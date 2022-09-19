#include <cpr/cpr.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <thread>

#include <cpr/cpr.h>
#include <json.hpp>
#include <td/spec/v1.hpp>

void load_games(const td::dl& base, const td::job& job)
{
start:
    using std::chrono::operator""ms;
    std::this_thread::sleep_for(250ms);

    auto data = nlohmann::json::parse(job->get_job_data());

    std::string key = data["key"].get<std::string>();
    auto rsp = cpr::Get(cpr::Url { "https://api.itch.io/games/" + std::to_string(data["game_id"].get<int>()) + "/uploads" },
        cpr::Header { { "Authorization", base->get_secret("API_KEY") } },
        cpr::Parameters { { "download_key_id", std::to_string(data["id"].get<int>()) } });

    auto uploads = nlohmann::json::parse(rsp.text);

    std::string name = data["game"]["title"].get<std::string>();

    for (auto u : uploads["uploads"]) {
        std::string fname = u["filename"].get<std::string>();
        nlohmann::json job_object = {
            { "upload", u },
            { "game", data },
            { "key", key },
            { "mode", 2 }
        };

        std::string key2 = key + "/" + fname;
        base->add_job(key2, name + " - " + fname, job_object.dump());
    }

    if ((uploads["uploads"].is_object() || uploads["uploads"].empty()) && (data["downloads"].get<int>() != 0)) {
        job->set_complete(data.dump(), true);
        return;
    }

    job->set_complete(data.dump(), false);
}