#include <cpr/cpr.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <td/spec/v1.hpp>

std::string key = "apod";
std::string name = "NASA Astronomy Picture of the Day";
std::string description = "Download the NASA Image of the Day";
std::vector<std::string> required_confs = {};
std::vector<std::string> required_secrets = { "API_KEY" };

void get_jobs(const td::dl& base)
{
    // Get APOD's JSON
    auto rsp = cpr::Get(cpr::Url { "https://api.nasa.gov/planetary/apod" },
        cpr::Parameters { { "api_key", base->get_secret("API_KEY") } });

    auto json = nlohmann::json::parse(rsp.text);

    // Create Output
    std::filesystem::path path = base->get_outpath_folder();
    path /= json["date"];
    std::filesystem::create_directory(path);

    // create data for future jobs
    nlohmann::json json_1 = {
        { "url", json["url"] },
        { "date", json["date"] },
        { "json_dump", false }
    };
    nlohmann::json json_2 = {
        { "url", json["hdurl"] },
        { "date", json["date"] },
        { "json_dump", false }
    };

    nlohmann::json json_3 = {
        { "date", json["date"] },
        { "json_dump", true },
    };

    json_3["data"] = json;

    // Add jobs for the JSONs
    base->add_job(json["date"].get<std::string>() + "image1", "APOD: " + json["date"].get<std::string>() + " (Image 1)", json_1.dump());
    base->add_job(json["date"].get<std::string>() + "image2", "APOD: " + json["date"].get<std::string>() + " (Image 2)", json_2.dump());
    base->add_job(json["date"].get<std::string>() + "json", "APOD: " + json["date"].get<std::string>() + " (Json Metadata)", json_3.dump());
}

void process_job(const td::dl& base, const td::job& job)
{
    // decode
    auto json = nlohmann::json::parse(job->get_job_data());

    auto path = std::filesystem::path(base->get_outpath_folder()) / json["date"].get<std::string>();
    std::filesystem::create_directory(path);

    if (json["json_dump"]) {
        std::ofstream outfile(path / "data.json");
        outfile << json["data"];
        outfile.close();
        job->set_complete(json.dump(), true);
    } else {

        auto uri = std::filesystem::path(json["url"].get<std::string>());

        std::ofstream outfile(path / uri.filename(), std::ios::binary);
        const cpr::WriteCallback write_cb([&](std::string data, intptr_t) -> bool {
            outfile << data;
            return true;
        });

        const cpr::ProgressCallback prog_cb([&](cpr::cpr_off_t total, cpr::cpr_off_t now, cpr::cpr_off_t, cpr::cpr_off_t, intptr_t) -> bool {
            job->set_progress(static_cast<float>(now) / static_cast<float>(total));
            return true;
        });

        auto rsp = cpr::Get(cpr::Url { json["url"] },
            write_cb, prog_cb);
    }
}

bool should_skip(const td::dl& base, const td::job& job)
{
    // decode
    auto json = nlohmann::json::parse(job->get_job_data());

    auto path = std::filesystem::path(base->get_outpath_folder()) / json["date"].get<std::string>();

    if (json["json_dump"]) {
        return std::filesystem::exists(path / "data.json");
    }
    auto uri = std::filesystem::path(json["url"].get<std::string>());
    return std::filesystem::exists(path / uri.filename());
}