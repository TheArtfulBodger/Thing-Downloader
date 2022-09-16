#include <iostream>
#include <td/minimal/downloader.hpp>
#include <td/minimal/job.hpp>

void td::minimal_downloader::add_job(std::string key, std::string data)
{
    if (jobs.find(key) == jobs.end()) {
        auto job = std::make_shared<td::minimal_job>(key, data);
        jobs[key] = job;
        job_queue.push(job);
    }
}

std::string td::minimal_downloader::get_secret(std::string key)
{
    if (secrets.find(key) != secrets.end()) {
        return secrets[key];
    }
    return "";
}

void td::minimal_downloader::set_secret(std::string key, std::string value)
{
    secrets[key] = value;
}

std::string td::minimal_downloader::get_conf(std::string key)
{
    if (confs.find(key) != confs.end()) {
        return confs[key];
    }
    return "";
}

void td::minimal_downloader::set_conf(std::string key, std::string value)
{
    confs[std::move(key)] = std::move(value);
}

std::string td::minimal_downloader::get_outpath_folder()
{
    return "";
}