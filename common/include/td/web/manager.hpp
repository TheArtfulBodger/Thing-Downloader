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
    // std::unordered_map<std::string, job_t> jobs;
    std::atomic<bool> should_quit;

    void thread_loop();
    bool loop_pop_queue();
    bool loop_job_queue();

    std::queue<job_t> job_queue;
    std::mutex job_mutex;

    std::vector<job_t> completed_list;
    std::mutex completed_mutex;

    std::vector<job_t> failed_list;
    std::mutex failed_mutex;

    std::vector<job_t> skipped_list;
    std::mutex skipped_mutex;

    std::queue<std::shared_ptr<thin_downloader>> load_queue;
    std::mutex load_mutex;

    std::mutex active_job_mutex;
    std::unordered_map<std::thread::id, job_t> active_jobs;

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

    /** @brief Get the job queue */
    std::queue<job_t> get_job_queue();

    /** @brief Get the list of active jobs */
    std::unordered_map<std::thread::id, job_t> get_active_jobs();

    /** @brief Get the completed jobs */
    std::vector<job_t> get_completed_jobs();

    /** @brief Get the failed jobs */
    std::vector<job_t> get_failed_jobs();

    /** @brief Get the skipped jobs */
    std::vector<job_t> get_skipped_jobs();

    /** @brief Get the loaded plugins */
    std::unordered_map<std::string, std::shared_ptr<thin_downloader>> get_plugins();

    /** @brief Get the plugin as a json object */
    std::string plugin_to_json(std::string&);

    /** @brief Set a secret value */
    void secrets_set(std::string& plugin, std::string& key, std::string& value);

    /** @brief Set a configuration value */
    void confs_set(std::string& plugin, std::string& key, std::string& value);
};

/*!
 * @brief Thin Downloader, interfaces with `td::web::downloader`
 */
class thin_downloader : public std::enable_shared_from_this<thin_downloader>, public td::downloader_base {
    std::weak_ptr<downloader> main_downloader;
    friend class downloader;

public:
    /** @brief The plugin object */
    plugin_t plugin;
    void add_job(std::string key, std::string name, std::string data) override;
    std::string get_secret(std::string key) override;
    void set_secret(std::string key, std::string value) override;
    std::string get_conf(std::string key) override;
    std::string get_outpath_folder() override;

    /** @brief The output folder */
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
    std::string plugin_id()
    {
        return plugin->key;
    }
};

using thin_t = std::weak_ptr<thin_downloader>;

} // namespace td
