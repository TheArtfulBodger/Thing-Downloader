#include <cpr/cpr.h>

#include <iostream>
#include <regex>

#include <json.hpp>
#include <td/spec/v1.hpp>

void get_jobs(const td::dl& base)
{

    std::regex url("https://(.+)\\.itch\\.io/(.+)");
    int i = 1;
    while (true) {
        auto rsp = cpr::Get(cpr::Url { "https://api.itch.io/profile/owned-keys" },
            cpr::Header { { "Authorization", base->get_secret("API_KEY") } },
            cpr::Parameters { { "page", std::to_string(i) } });

        auto json = nlohmann::json::parse(rsp.text);
        if (json["owned_keys"].empty()) {
            break;
        }

        for (auto& g : json["owned_keys"]) {
            std::smatch m;
            std::string u = g["game"]["url"].get<std::string>();
            std::regex_search(u, m, url);

            std::string key = std::string(m[1]) + "/" + std::string(m[2]);

            g["key"] = key;
            g["mode"] = 1;
            base->add_job(key, "Loading Games for: " + g["game"]["title"].get<std::string>(), g.dump());
        }
        i++;
    }
}
