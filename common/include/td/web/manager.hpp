#pragma once
#include <atomic>
#include <filesystem>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

#include <td/spec/v1.hpp>
#include <td/store.hpp>
#include <td/web/job.hpp>

namespace td::web {

/*!
 * @brief Full Downloade, used in `webmain`
 */
class downloader : public std::enable_shared_from_this<downloader> {
    friend class thin_downloader;

    std::vector<std::thread> thread_pool;
    std::unordered_map<std::string, std::shared_ptr<thin_downloader>> plugins;
    std::unordered_map<std::string, job_t> jobs;
    std::atomic<bool> should_quit;

    void thread_loop();
    void loop_pop_queue();
    void loop_job_queue();

    std::queue<job_t> job_queue;
    std::mutex job_mutex;

    std::queue<std::shared_ptr<thin_downloader>> load_queue;
    std::mutex load_mutex;

    store_t secrets;
    store_t confs;

    std::filesystem::path outpath;

public:
    /*!
     * @brief Construct a new downloader object
     *
     * @param threads `int` The number of additional threads to use.
     * @param outpath `std::filesystem::path` the output directory.
     * @param secrets shared pointer to secrets store
     * @param confs shared pointer to config store
     */
    downloader(int threads, std::filesystem::path outpath, store_t secrets, store_t confs);

    ~downloader();

    /*! @brief Adds a plugin from the path */
    void add_plugin(std::string);

    /*!
     * @brief Runs a plugin's load_jobs function
     * @param plugin `std::string` the key for the plugin
     */
    void get_jobs_plugin(std::string plugin);

    /*! @brief Runs the thread loop once
     *  @details required for use if threads is set to 0
     */
    void loop_once();

    std::queue<job_t> get_job_queue();
    std::unordered_map<std::string, job_t> get_jobs();
};

/*!
 * @brief Thin Downloader, interfaces with `td::web::downloader`
 */
class thin_downloader : public std::enable_shared_from_this<thin_downloader>, public td::downloader_base {
    plugin_t plugin;
    std::weak_ptr<downloader> main_downloader;
    friend class downloader;

public:
    void add_job(std::string key, std::string data) override;
    std::string get_secret(std::string key) override;
    void set_secret(std::string key, std::string value) override;
    std::string get_conf(std::string key) override;
    std::string get_outpath_folder() override;

    std::filesystem::path outpath;

    /*! @brief Construct a new downloader object. */
    explicit thin_downloader(std::shared_ptr<downloader> main_downloader, plugin_t plugin)
        : main_downloader(main_downloader)
        , plugin(plugin)
    {
        outpath = main_downloader->outpath / plugin->key;
        std::filesystem::create_directory(outpath);
    }

    /*! @brief Destroy the downloader object. */
    ~thin_downloader() = default;
    
    /*! @brief Returns the name of the plugin being used */
    std::string plugin_id() {
        return plugin->key;
    }
};

using thin_t = std::weak_ptr<thin_downloader>;

} // namespace td
