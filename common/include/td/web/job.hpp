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
    }

    std::string get_job_data() override { return data; }

    job(std::string key, std::string data, thin_t thin)
        : key(std::move(key))
        , data(std::move(data))
        , thin(thin)
    {
    }

    [[nodiscard]] state get_job_state() const { return job_state; }

    float progress;
    std::string key;
    std::string status;
    bool completed;
    bool failed;
    std::string data;
    thin_t thin;
    state job_state;

    std::string to_json();
};

using job_t = std::shared_ptr<job>;

} // namespace td
