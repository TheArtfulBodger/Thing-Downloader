#include <iostream>
#include <json.hpp>
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

std::unordered_map<std::thread::id, td::web::job_t> td::web::downloader::get_active_jobs()
{
    std::lock_guard<std::mutex> lock(active_job_mutex);
    return std::unordered_map<std::thread::id, td::web::job_t>(active_jobs);
}

std::queue<td::web::job_t> td::web::downloader::get_job_queue()
{
    std::lock_guard<std::mutex> lock(job_mutex);
    return std::queue<td::web::job_t>(job_queue);
}

std::vector<td::web::job_t> td::web::downloader::get_completed_jobs()
{
    std::lock_guard<std::mutex> lock(completed_mutex);
    return std::vector<td::web::job_t>(completed_list);
}

std::vector<td::web::job_t> td::web::downloader::get_failed_jobs()
{
    std::lock_guard<std::mutex> lock(failed_mutex);
    return std::vector<td::web::job_t>(failed_list);
}

std::vector<td::web::job_t> td::web::downloader::get_skipped_jobs()
{
    std::lock_guard<std::mutex> lock(skipped_mutex);
    return std::vector<td::web::job_t>(skipped_list);
}

std::unordered_map<std::string, std::shared_ptr<td::web::thin_downloader>> td::web::downloader::get_plugins()
{
    return plugins;
}

std::string td::web::downloader::plugin_to_json(std::string& key)
{
    auto c = plugins[key];

    bool c_ = true;
    auto _conf_keys = confs->get_keys(key);
    for (auto& req_key : c->plugin->required_confs) {
        if (std::find(_conf_keys.begin(), _conf_keys.end(), req_key) == _conf_keys.end()) {
            c_ = false;
            break;
        }
    }
    nlohmann::json configuration;
    for (auto& _c : _conf_keys) {
        configuration[_c] = confs->get(key, _c);
    }

    bool s_ = true;
    auto _secret_keys = secrets->get_keys(key);
    for (auto& req_key : c->plugin->required_secrets) {
        if (std::find(_secret_keys.begin(), _secret_keys.end(), req_key) == _secret_keys.end()) {
            s_ = false;
            break;
        }
    }

    nlohmann::json k = {
        { "name", c->plugin->name },
        { "description", c->plugin->description },
        { "required_confs", c->plugin->required_confs },
        { "required_secrets", c->plugin->required_secrets },
        { "set_confs", configuration },
        { "set_secrets", _secret_keys },
        { "has_required_confs", c_ },
        { "has_required_secrets", s_ }

    };
    return k.dump();
}

/*
bool td::web::downloader::has_required_config(td::plugin_t p)
{
    auto cs = confs->get_keys(p->key);
    for (auto& c : p->required_confs) {
        if (std::find(cs.begin(), cs.end(), c) == cs.end()) {
            return false;
        }
    }
    return true;
}

bool td::web::downloader::has_required_secrets(td::plugin_t p)
{
    auto cs = secrets->get_keys(p->key);
    for (auto& c : p->required_secrets) {
        if (std::find(cs.begin(), cs.end(), c) == cs.end()) {
            return false;
        }
    }
    return true;
}


*/

void td::web::downloader::secrets_set(std::string& plugin, std::string& key, std::string& value)
{
    secrets->set(plugin, key, value);
}

void td::web::downloader::confs_set(std::string& plugin, std::string& key, std::string& value)
{
    confs->set(plugin, key, value);
}
