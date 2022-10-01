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
    void set_complete(std::string result, bool fail) override
    {
        data = result;
        failed = fail;
    }

    std::string get_job_data() override { return data; }

    /**
     * @brief Construct a new minimal job object
     *
     * @param key `std::string` *Unique* string representing the downloader (preferably a product ID and not a URL)
     * @param name `std::string` Human Readable name for the download job
     * @param data `std::string` json encoded string for the job
     */
    minimal_job(std::string key, std::string name, std::string data)
        : key(std::move(key))
        , name(name)
        , data(std::move(data))
    {
    }

private:
    float progress;
    std::string key;
    std::string name;
    std::string status;
    bool completed;
    bool failed;
    std::string data;
};

} // namespace td
