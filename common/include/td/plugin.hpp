#pragma once

#include <functional>

#include <td/spec/v1.hpp>

namespace td {
/*!
 * @brief Plugin class, contains nice wrapper of functions and members loaded in from their dynamic library
 */
class plugin : std::enable_shared_from_this<plugin> {
public:
    // Technically, these are writable, but that shouldn't be an issue.

    /*! @brief *Unique* identifier of the plugin. Should only contain lowercase letters, numbers and hyphens.*/
    std::string key;

    /*! @brief Name of the plugin in the UI, can contain any characters. */
    std::string name;

    /*! @brief  Description of the plugin for the UI */
    std::string description;

    /*! @brief List of required configuration variables for the plugin to function. */
    std::vector<std::string> required_confs;

    /*! @brief List of required secrets for the plugin to function. */
    std::vector<std::string> required_secrets;

    /*! @brief `std::function` wrapper of `get_jobs()` */
    std::function<void(const dl&)> get_jobs;

    /*! @brief `std::function` wrapper of `process_job()` */
    std::function<void(const dl&, const job&)> process_job;

    /*! @brief `std::function` wrapper of `should_skip()` */
    std::function<bool(const dl&, const job&)> should_skip;

    /*!
     * @brief Construct a new plugin object
     * @param path `std::string` path to the dynamic library
     */
    explicit plugin(std::string& path);

    /*! @brief Destroy the plugin object */
    virtual ~plugin();

private:
    void* handle;
};
}