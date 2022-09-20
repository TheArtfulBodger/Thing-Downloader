#include <filesystem>
#include <fstream>
#include <iostream>

#include <json.hpp>
#include <td/spec/v1.hpp>

bool should_skip(const td::dl& base, const td::job& job)
{
    auto data = nlohmann::json::parse(job->get_job_data());
    int mode = data["mode"].get<int>();
    if (mode == 1) {
        return false;
    }

    auto folder = std::filesystem::path(base->get_outpath_folder()) / data["key"].get<std::string>();
    auto file = folder / data["upload"]["filename"].get<std::string>();
    auto md5_file = folder / (data["upload"]["filename"].get<std::string>() + ".md5");

    if (!std::filesystem::is_regular_file(file) || !std::filesystem::is_regular_file(md5_file)) {
        return false;
    }

    std::string md5;
    {
        std::ifstream t(md5_file);
        t.seekg(0, std::ios::end);
        md5.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        md5.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    }

    return (md5 == data["upload"]["md5_hash"].get<std::string>());

    // We only need to check for the existence of the md5 file on download.
    // If it's there, we move the old versions to an old/ subdirectory before we download
}

void load_games(const td::dl& base, const td::job& job);
void download_file(const td::dl& base, const td::job& job);

void process_job(const td::dl& base, const td::job& job)
{
    auto data = nlohmann::json::parse(job->get_job_data());
    int mode = data["mode"].get<int>();

    switch (mode) {
    case 1:
        load_games(base, job);
        break;
    case 2:
        download_file(base, job);
        break;
    default:
        return;
    }
}