#include <cpr/cpr.h>
#include <iostream>

#include <Document.h>
#include <Node.h>
#include <Selection.h>

#include <json.hpp>
#include <td/spec/v1.hpp>

void get_jobs(const td::dl& base)
{
    auto rsp = cpr::Get(
        cpr::Url { "https://www.humblebundle.com/home/library" },
        cpr::Cookies({ { "_simpleauth_sess", base->get_secret("_SIMPLEAUTH_SESS") }, false }));

    CDocument doc;
    doc.parse(rsp.text);

    auto data_elem = doc.find("#user-home-json-data");

    if (data_elem.nodeNum() == 0) {
        std::cerr << "No json object in response" << std::endl;
    }
    auto j = nlohmann::json::parse(data_elem.nodeAt(0).text());

    for (auto x : j["gamekeys"]) {
        std::string u = "https://www.humblebundle.com/api/v1/order/" + x.get<std::string>() + "?all_tpkds=true";

        auto rsp2 = cpr::Get(
            cpr::Url { u },
            cpr::Cookies({ { "_simpleauth_sess", base->get_secret("_SIMPLEAUTH_SESS") }, false }));

        auto data = nlohmann::json::parse(rsp2.text);

        for (auto g : data["subproducts"]) {
            nlohmann::json new_g = g;
            new_g["parent"] = data["product"];

            base->add_job(
                g["machine_name"].get<std::string>(),
                data["product"]["human_name"].get<std::string>() + " - " + g["human_name"].get<std::string>(), new_g.dump());
        }
    }
}
