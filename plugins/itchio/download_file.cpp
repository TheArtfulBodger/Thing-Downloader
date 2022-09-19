#include <cpr/cpr.h>

#include <cmath>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <json.hpp>
#include <td/spec/v1.hpp>

static const char* humanSize(uint64_t bytes)
{
    char* suffix[] = { "Bytes", "KiB", "MiB", "GiB", "TiB" };
    char length = sizeof(suffix) / sizeof(suffix[0]);

    int i = 0;
    double dblBytes = bytes;

    if (bytes > 1024) {
        for (i = 0; (bytes / 1024) > 0 && i < length - 1; i++, bytes /= 1024)
            dblBytes = bytes / 1024.0;
    }

    static char output[200];
    sprintf(output, "%.02lf %s", dblBytes, suffix[i]);
    return output;
}

void download_file(const td::dl& base, const td::job& job)
{
    auto data = nlohmann::json::parse(job->get_job_data());

    auto folder = std::filesystem::path(base->get_outpath_folder()) / data["key"].get<std::string>();
    std::filesystem::create_directories(folder);

    auto file = folder / data["upload"]["filename"].get<std::string>();
    auto md5_file = folder / (data["upload"]["filename"].get<std::string>() + ".md5");

    if (std::filesystem::is_regular_file(md5_file)) {
        job->set_status("Moving Pervious Version of File to subdirectory");

        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::ostringstream ss;
        ss << std::put_time(&tm, "%F") ;
        auto old = folder / "old" / ss.str();

        std::filesystem::create_directories(old);
        std::filesystem::rename(file, old / data["upload"]["filename"].get<std::string>());
        std::filesystem::rename(md5_file, old / (data["upload"]["filename"].get<std::string>() + ".md5"));
    }

    std::ofstream of(file, std::ios::binary);

    cpr::ProgressCallback
    prog([&](size_t downloadTotal, size_t downloadNow, size_t uploadTotal,
             size_t uploadNow, intptr_t) -> bool {
        float prog = 100 * ((float)downloadNow) / (downloadTotal + 1);
        job->set_progress(prog);
        std::string status = std::to_string(prog).substr(0, 5) + "% of " + humanSize(downloadTotal);
        job->set_status(status);
        return true;
    });

    cpr::WriteCallback
    write([&](std::string data, intptr_t) -> bool {
        of.write(data.c_str(), data.size());
        return true;
    });

    cpr::Get(cpr::Url { "https://api.itch.io/uploads/" + std::to_string(data["upload"]["id"].get<int>()) + "/download" },
        cpr::Parameters {
            { "download_key_id", std::to_string(data["game"]["id"].get<int>()) },
            { "api_key", base->get_secret("API_KEY") } },
        write, prog);
    {
        std::ofstream of2(md5_file);
        of2 << data["upload"]["md5_hash"].get<std::string>();
    }
    job->set_complete(data.dump(), false);
}