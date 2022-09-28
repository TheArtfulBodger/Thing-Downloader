#include <filesystem>
#include <fstream>
#include <iostream>

#include <cpr/cpr.h>

#include <json.hpp>
#include <td/spec/v1.hpp>

void process_job(const td::dl& base, const td::job& job)
{

    auto data = nlohmann::json::parse(job->get_job_data());

    for (auto dl : data["downloads"]) {
        auto p = std::filesystem::path(base->get_outpath_folder()) / data["parent"]["human_name"].get<std::string>() / data["human_name"].get<std::string>();

        std::filesystem::create_directories(p);
        int n = dl["download_struct"].size();
        int i = 0;

        for (auto g : dl["download_struct"]) {
            std::string url = g["url"]["web"].get<std::string>();
            std::string rg = url.substr(0, url.find_first_of('?'));
            std::string file = rg.substr(rg.find_last_of('/') + 1);

            auto out_path = p / file;

            if (std::filesystem::exists(out_path)) {
                i++;
                continue;
            }

            // check for md5 or sha-1 file

            std::ofstream of(out_path, std::ios::binary);

            cpr::ProgressCallback
            prog([&](size_t d_total, size_t d_now, size_t /*u_total*/,
                     size_t /*u_now*/, intptr_t /*usr_data*/) -> bool {
                if (d_total != 0) {
                    float prog = 100 * static_cast<float>(d_now) / (d_total + 1);
                    float p = prog;
                    prog += i * 100;
                    prog /= n;
                    job->set_progress(prog);
                    std::string status = std::to_string(p);
                    status += "% of ";
                    status += g["human_size"].get<std::string>();
                    status += " (";
                    status += std::to_string(i + 1);
                    status += " of ";
                    status += std::to_string(n);
                    status += ")";

                    job->set_status(status);
                } else {
                    job->set_status("Waiting for response");
                }
                return true;
            });

            cpr::WriteCallback
            write([&](std::string data, intptr_t /*usr_data*/) -> bool {
                of.write(data.c_str(), data.size());
                return true;
            });

            cpr::Get(cpr::Url { url },
                cpr::Cookies({ { "_simpleauth_sess", base->get_secret("_SIMPLEAUTH_SESS") }, false }),
                write, prog);

            /*if (data["upload"]["md5_hash"].is_string()) {
                std::ofstream of2(md5_file);
                of2 << data["upload"]["md5_hash"].get<std::string>();
            }*/

            i++;
        }
    }

    job->set_complete(job->get_job_data(), false);
}