#pragma once
#include <filesystem>
#include <queue>
#include <unordered_map>

#include <td/plugin.hpp>
#include <td/spec/v1.hpp>

namespace td::web {

enum state {
    unprocessed,
    skipped,
    downloading,
    completed,
    failed
};

class thin_downloader;
using thin_t = std::weak_ptr<thin_downloader>;

/*!
 * @brief Minimal job example, used in the `td_test` utility
 */
class job : public td::job_base {
public:
    void set_status(std::string stat) override { status = stat; }
    void set_progress(float prog) override { progress = prog; }
    void set_complete(std::string result, bool fail) override
    {
        data = result;
        failed = fail;
        job_state = failed ? td::web::failed : td::web::completed;
        progress = 100;
    }

    std::string get_job_data() override { return data; }

    /**
     * @brief Construct a new job object
     *
     * @param key `std::string` *Unique* string representing the downloader (preferrably a product ID and not a URL)
     * @param name `std::string` Human Readable name for the download job
     * @param data `std::string` json encoded string for the job
     * @param thin `thin_t` Thin downloader object representing the plugin
     */
    job(std::string key, std::string name, std::string data, thin_t thin)
        : key(std::move(key))
        , name(name)
        , data(std::move(data))
        , thin(thin)
    {
    }

    /**
     * @brief Get the object's job state
     * @return state
     */
    [[nodiscard]] state get_job_state() const { return job_state; }

    /**
     * @brief
     *
     * @return `std::string` json encoded string of the object (for rpc functions)
     */
    std::string to_json();

private:
    float progress { 0.0F };
    std::string key;
    std::string status;
    std::string name;
    bool completed;
    bool failed;
    std::string data;
    thin_t thin;
    state job_state { unprocessed };

    friend class downloader;
};

using job_t = std::shared_ptr<job>;

} // namespace td
