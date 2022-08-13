#pragma once
#include <queue>
#include <unordered_map>

#include <td/plugin.hpp>
#include <td/spec/v1.hpp>

namespace td::web {

class thin_downloader;
using thin_t = std::weak_ptr<thin_downloader>;

/*!
 * @brief Minimal job example, used in the `td_test` utility
 */
class job : public td::job_base {
public:
    void set_status(std::string stat) override { status = stat; }
    void set_progress(float prog) override { progress = prog; }
    void set_complete(buffer result, bool fail) override
    {
        data = result;
        failed = fail;
    }

    buffer get_job_data() override { return data; }

    job(std::string key, buffer data, thin_t thin)
        : key(std::move(key))
        , data(std::move(data))
        , thin(thin)
    {
    }

    float progress;
    std::string key;
    std::string status;
    bool completed;
    bool failed;
    buffer data;
    thin_t thin;
};

using job_t = std::shared_ptr<job>;

} // namespace td
