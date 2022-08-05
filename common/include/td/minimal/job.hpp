#pragma once
#include <queue>
#include <unordered_map>

#include <td/spec/v1.hpp>

namespace td {
/*!
 * @brief Minimal job example, used in the `td_test` utility
 */
class minimal_job : public td::job_base {
public:
    void set_status(std::string stat) override { status = stat; }
    void set_progress(float prog) override { progress = prog; }
    void set_complete(buffer result, bool fail) override
    {
        data = result;
        failed = fail;
    }

    buffer get_job_data() override { return data; }

    minimal_job(std::string key, buffer data)
        : key(std::move(key))
        , data(std::move(data))
    {
    }

    float progress;
    std::string key;
    std::string status;
    bool completed;
    bool failed;
    buffer data;
};

} // namespace td
