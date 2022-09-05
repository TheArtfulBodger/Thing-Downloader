#include <td/web/manager.hpp>

void td::web::downloader::thread_loop()
{
    while (not should_quit) {
        loop_once();
    }
}

void td::web::downloader::loop_once()
{
    loop_pop_queue();
    loop_job_queue();
    using std::chrono::operator""ms;
    std::this_thread::sleep_for(2000ms);
}

// See if loading jobs is requested
void td::web::downloader::loop_pop_queue()
{
    std::shared_ptr<thin_downloader> thin;

    {
        std::lock_guard<std::mutex> lock(load_mutex);

        if (load_queue.empty()) {
            return;
        }

        thin = load_queue.front();

        load_queue.pop();
    }

    thin->plugin->get_jobs(thin);
}
// Get Job

void td::web::downloader::loop_job_queue()
{
    td::web::job_t job;

    {
        std::lock_guard<std::mutex> lock(job_mutex);

        if (job_queue.empty()) {
            return;
        }

        job = job_queue.front();
        job_queue.pop();
    }

    auto thin = job->thin.lock();

    // See if it should be skipped
    if (thin->plugin->should_skip(thin, job)) {
        return;
    }

    thin->plugin->process_job(thin, job);
}
