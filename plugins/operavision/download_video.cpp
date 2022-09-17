#include <cpr/cpr.h>

#include <filesystem>
#include <regex>
#include <td/spec/v1.hpp>

#include <subprocess.hpp>

#include "opera.hpp"

// yt-dl uses frequent carrige returns to reset the line, this is an alternative implementation to std::getline which accounts for both
bool get_line(std::istream& stream, std::string& delims, std::string& line)
{
    line.erase();
    char c;
    while (stream.get(c)) {
        if (delims.find(c) != std::string::npos) {
            return true;
        }
        line += c;
    }
    return false;
}

void download_video(const td::dl& base, const td::job& job)
{
    auto o = nlohmann::json::parse(job->get_job_data()).get<opera>();

    auto folder = std::filesystem::path(base->get_outpath_folder()) / o.company / o.name;
    std::filesystem::create_directories(folder);

    subprocess::popen cmd(base->get_conf("YOUTUBE_DL_PATH"),
        { "--write-sub",
            "--all-subs",
            "--embed-subs",
            "https://youtu.be/" + o.video_id, "-o", folder.string() + "/" + o.slug + ".%(ext)s",
            "--restrict-filenames" });

    auto r1 = std::regex("\\[download\\][ ]+([0-9.]+)% of ([0-9.]+)(B|KiB|MiB|GiB) at[ ]+([0-9.]+)(B|KiB|MiB|GiB)/s ETA ([0-9:]+)");
    // Add More Regex for more output lines

    std::string delims = "\n\r";
    for (std::string line; get_line(cmd.stdout(), delims, line);) {
        std::smatch m;

        std::regex_search(line, m, r1);
        if (!m.empty()) {

            job->set_progress(std::stof(m[1]));
            std::string status = std::string(m[1]) + "% of " + std::string(m[2]) + std::string(m[3]) + std::string(" (") + std::string(m[6]) + std::string(")");
            job->set_status(status);
        } else {
            // Check more regex Lines
        }
    }

    cmd.wait();

    job->set_complete(job->get_job_data(), false);
}