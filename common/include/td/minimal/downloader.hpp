#pragma once
#include <queue>
#include <unordered_map>

#include <td/spec/v1.hpp>

namespace td {
/*!
 * @brief Minimal Downloader example, used in the `td_test` utility
 */
class minimal_downloader : public td::downloader_base {
public:
    void add_job(std::string key, std::string data) override;
    std::string get_secret(std::string key) override;
    void set_secret(std::string key, std::string value) override;
    std::string get_conf(std::string key) override;
    std::string get_outpath_folder() override;

    /*!
     * @brief Sets a configuration
     * @param key `std::string` The key / label for the secret
     * @param value `std::string` The secret value
     */
    void set_conf(std::string key, std::string value);

    /*! @brief Construct a new minimal downloader object. */
    minimal_downloader() = default;
    /*! @brief Destroy the minimal downloader object. */
    ~minimal_downloader() = default;

    /*! @brief Hashmap to store configuration values, public debugging purposes. */
    std::unordered_map<std::string, std::string> confs;

    /*! @brief Hashmap to store secrets, public debugging purposes. */
    std::unordered_map<std::string, std::string> secrets;

    /*! @brief Hashmap to store job details, public debugging purposes. */
    std::unordered_map<std::string, job> jobs;

    /*! @brief Job queue, public debugging purposes. */

    std::queue<job> job_queue;
};

} // namespace td
