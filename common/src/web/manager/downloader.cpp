#include <iostream>
#include <td/web/manager.hpp>

td::web::downloader::downloader(int threads, std::filesystem::path outpath, store_t secrets, store_t confs)
    : outpath(outpath)
    , secrets(secrets)
    , confs(confs)
    , should_quit(false)
{

    for (int i = 0; i < threads; i++) {
        std::thread t(&td::web::downloader::thread_loop, this);
        thread_pool.emplace_back(std::move(t));
    }
}

td::web::downloader::~downloader()
{
    should_quit = true;
    for (auto& i : thread_pool) {
        i.join();
    }
}

void td::web::downloader::add_plugin(std::string path)
{
    auto p = std::make_shared<td::plugin>(path);
    auto thin = std::make_shared<td::web::thin_downloader>(shared_from_this(), p);

    plugins.insert(std::make_pair(p->key, thin));
}

void td::web::downloader::get_jobs_plugin(std::string plugin)
{
    std::lock_guard<std::mutex> lock(load_mutex);

    load_queue.push(plugins[plugin]);
}
