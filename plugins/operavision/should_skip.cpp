#include <filesystem>
#include <iostream>

#include <td/spec/v1.hpp>

#include "opera.hpp"

bool should_skip(const td::dl& base, const td::job& job)
{
    // decode job
    auto o = nlohmann::json::parse(job->get_job_data()).get<opera>();

    switch (o.operation) {
    case download_mode_video: {
        auto folder = std::filesystem::path(base->get_outpath_folder()) / o.company / o.name;
        auto mp4 = folder / (o.slug + ".mp4");
        auto mkv = folder / (o.slug + ".mkv");
        auto webm = folder / (o.slug + ".webm");
        return std::filesystem::exists(mp4)
            or std::filesystem::exists(mkv)
            or std::filesystem::exists(webm);
    }
    case download_mode_desc: {
        auto path = std::filesystem::path(base->get_outpath_folder()) / o.company / o.name / (o.slug + ".nfo");
        return std::filesystem::exists(path);
    }
    default:
        return true;
    }
}

void download_description(const td::dl& base, const td::job& job);
void download_video(const td::dl& base, const td::job& job);

void process_job(const td::dl& base, const td::job& job)
{
    auto o = nlohmann::json::parse(job->get_job_data()).get<opera>();

    switch (o.operation) {
    case download_mode_video:
        download_video(base, job);
        break;
    case download_mode_desc:
        download_description(base, job);
        break;

    default: {
        std::string data = R"({"error":"Unknown Value for download mode"})";
        job->set_complete(data, true);
    }
    }
}