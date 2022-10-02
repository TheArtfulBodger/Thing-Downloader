#include <td/web/manager.hpp>

void td::web::downloader::thread_loop()
{
    while (!should_quit) {
        loop_once();
    }
}

void td::web::downloader::loop_once()
{
    bool pop = loop_pop_queue();
    bool job = loop_job_queue();
    if (!(pop || job)) {
        // Only sleep if the queue is empty
        using std::chrono::operator""ms;
        std::this_thread::sleep_for(2000ms);
    }
}

// See if loading jobs is requested
bool td::web::downloader::loop_pop_queue()
{
    std::shared_ptr<thin_downloader> thin;

    {
        std::lock_guard<std::mutex> lock(load_mutex);

        if (load_queue.empty()) {
            return false;
        }

        thin = load_queue.front();

        load_queue.pop();
    }

    thin->plugin->get_jobs(thin);
    return true;
}
// Get Job

bool td::web::downloader::loop_job_queue()
{
    td::web::job_t job;

    {
        std::lock_guard<std::mutex> lock(job_mutex);

        if (job_queue.empty()) {
            return false;
        }

        job = job_queue.front();
        job_queue.pop();
    }

    auto thin = job->thin.lock();

    // See if it should be skipped
    if (thin->plugin->should_skip(thin, job)) {
        job->job_state = td::web::skipped;
        job->set_progress(100.0F);
        std::lock_guard<std::mutex> lock(skipped_mutex);
        skipped_list.push_back(job);
        return true;
    }

    {
        std::lock_guard<std::mutex> lock(active_job_mutex);
        active_jobs.insert(std::make_pair(std::this_thread::get_id(), job));
    }

    job->job_state = td::web::downloading;
    thin->plugin->process_job(thin, job);

    {
        std::lock_guard<std::mutex> lock(active_job_mutex);
        active_jobs.erase(std::this_thread::get_id());
    }

    // Now add it to the relevant queues
    if (job->job_state == failed) {
        std::lock_guard<std::mutex> lock(failed_mutex);
        failed_list.push_back(job);
    } else {
        std::lock_guard<std::mutex> lock(completed_mutex);
        completed_list.push_back(job);
    }

    return true;
}
