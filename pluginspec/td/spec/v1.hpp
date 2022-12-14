#pragma once
#include <memory>
#include <string>
#include <vector>

#if defined(_MSC_VER) && defined(_DLL)
/*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

namespace td {

/*! @brief Abstract class representing a job*/
class job_base {
public:
    /*!
     * @brief Get the job's data
     * @return json encoded object for the job
     */
    virtual std::string get_job_data() = 0;

    /*!
     * @brief Set the status string
     * @param status `std::string` meaningful status of the job
     * (eg `Downloading Installer` or `Extracting Zip`)
     */
    virtual void set_status(std::string status) = 0;

    /*!
     * @brief Set the progress of the download
     * @param progress `float` Should be between 0 and 100
     */
    virtual void set_progress(float progress) = 0;

    /*!
     * @brief Set the complete object
     * @param data `std::string` json encoded string for the job
     * @param failed `bool` false if successfully completed, false if failed
     */
    virtual void set_complete(std::string data, bool failed) = 0;
};

/*! @brief Abstract class representing the downloader.*/
class downloader_base {
public:
    /*!
     * @brief Adds a jon object to the queue
     * @param key `std::string` *Unique* string representing the downloader (preferably a product ID and not a URL)
     * @param name `std::string` Human Readable name for the download job
     * @param data `std::string` json encoded string for the job
     */
    virtual void add_job(std::string key, std::string name, std::string data) = 0;

    /*!
     * @brief Get value of a stored secret.
     * @param key `std::string` The key / label for the secret
     * @return `std::string` The secret value
     */
    virtual std::string get_secret(std::string key) = 0;

    /*!
     * @brief Sets a secret
     * @details Secrets can be set during run-time to allow for update of login tokens or similar
     * @param key `std::string` The key / label for the secret
     * @param value `std::string` The secret value
     */
    virtual void set_secret(std::string key, std::string value) = 0;

    /*!
     * @brief Get configuration values.
     * @param key `std::string` The key / label for the secret
     * @return `std::string` The secret value
     */
    virtual std::string get_conf(std::string key) = 0;

    /*!
     * @brief Get the outpath directory to write downloads to.
     * @return `std::string` the path to the output directory
     */
    virtual std::string get_outpath_folder() = 0;
};

using job = std::shared_ptr<job_base>; /*!< @brief Alias for a job object pointer*/
using dl = std::shared_ptr<downloader_base>; /*!< @brief Alias for a pointer to the downloader*/
}

extern "C" {
// List of Symbols required for a plugin

/*! @brief Version of the specification implemented.*/
DLLEXPORT extern const int version;

/*! @brief *Unique* identifier of the plugin. Should only contain lowercase letters, numbers and hyphens.*/
DLLEXPORT extern std::string key;

/*! @brief Name of the plugin in the UI, can contain any characters. */
DLLEXPORT extern std::string name;

/*! @brief Description of the plugin for the UI, can contain any characters. */
DLLEXPORT extern std::string description;

/*! @brief List of required configuration variables for the plugin to function. */
DLLEXPORT extern std::vector<std::string> required_confs;

/*! @brief List of required secrets for the plugin to function. */
DLLEXPORT extern std::vector<std::string> required_secrets;

// WARNING: These Functions should operate as fully encapsulated functions, using no global state, and all job properties should be stored in the buffer, and secrets and configuration in the downloader object.

/*!
 * @brief Load all the downloadable jobs.
 * This will probably involve loading the library, and creating a job for each.
 * Jobs should be added via the td::downloader_base::add_job function
 * @param base Smart pointer to the base downloader object (td::downloader_base)
 */
DLLEXPORT void get_jobs(const td::dl& base);

/*!
 * @brief Executes the download job.
 * @param base Smart pointer to the base downloader object (td::downloader_base)
 * @param job Smart pointer to the job object (td::job_base)
 */
DLLEXPORT void process_job(const td::dl& base, const td::job& job);

/*!
 * @brief Checks if the job has been previously executed to avoid redownloading files that already exists.
 * @param base Smart pointer to the base downloader object (td::downloader_base)
 * @param job Smart pointer to the job object (td::job_base)
 * @return `false` If the job should continue
 * @return `true` If the job has been executed successfully previously
 */
DLLEXPORT bool should_skip(const td::dl& base, const td::job& job);
}

// NoDocsPage