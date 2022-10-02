#include <td/web/manager.hpp>

std::string td::web::thin_downloader::get_secret(std::string key)
{
    auto m = main_downloader.lock();
    return m->secrets->get(plugin->key, key);
}

void td::web::thin_downloader::set_secret(std::string key, std::string value)
{
    auto m = main_downloader.lock();
    return m->secrets->set(plugin->key, key, value);
}

std::string td::web::thin_downloader::get_conf(std::string key)
{
    auto m = main_downloader.lock();
    return m->confs->get(plugin->key, key);
}

std::string td::web::thin_downloader::get_outpath_folder()
{
    return outpath.string();
}

void td::web::thin_downloader::add_job(std::string key, std::string name, std::string data)
{
    auto m = main_downloader.lock();

    std::string k = plugin->key + "/" + key;

    auto job = std::make_shared<td::web::job>(k, name, data, shared_from_this());

    // m->jobs.insert(std::make_pair(k, job));

    {
        std::lock_guard<std::mutex> lock(m->job_mutex);
        m->job_queue.push(job);
    }
}