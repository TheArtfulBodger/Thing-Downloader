#include <cpr/cpr.h>

#include <filesystem>
#include <iostream>
#include <regex>
#include <sstream>
#include <td/spec/v1.hpp>

#include <process.hpp>

#include "opera.hpp"

void download_video(const td::dl& base, const td::job& job)
{

    auto r1 = std::regex("\\[download\\][ ]+([0-9.]+)% of ([0-9.]+)(B|KiB|MiB|GiB) at[ ]+([0-9.]+)(B|KiB|MiB|GiB)/s ETA ([0-9:]+)");
    // Add More Regex for more output lines

    auto o = nlohmann::json::parse(job->get_job_data()).get<opera>();

    auto folder = std::filesystem::path(base->get_outpath_folder()) / o.company / o.name;
    std::filesystem::create_directories(folder);

    std::stringstream stdout;

    TinyProcessLib::Process cmd(
        std::vector<std::string> { base->get_conf("YOUTUBE_DL_PATH"),
            "--write-sub",
            "--all-subs",
            "--embed-subs",
            "https://youtu.be/" + o.video_id, "-o", folder.string() + "/" + o.slug + ".%(ext)s",
            "--restrict-filenames" },
        "",
        [&](const char* bytes, size_t n) {
            std::string line(bytes, n);
            std::smatch m;

            std::regex_search(line, m, r1);
            if (!m.empty()) {

                job->set_progress(std::stof(m[1]));
                std::string status(m[1]);
                status += "% of ";
                status += m[2];
                status += m[3];
                status += " (";
                status += m[6];
                status += ")";
                job->set_status(status);
            } else {
                // Check more regex Lines
            }
        });

    int i = cmd.get_exit_status();

    job->set_complete(job->get_job_data(), i != 0);
}