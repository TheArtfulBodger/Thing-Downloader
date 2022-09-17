#include <td/web/rpc_functions.hpp>

td::web::rpc_t td::web::rpc::get_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& params) {
    nlohmann::json l = nlohmann::json::array();
    for (auto& c : dl->get_jobs()) {
        nlohmann::json k = {
            { "key", c.first },
            { "value", nlohmann::json::parse(c.second->to_json()) },
            { "plugin", c.second->thin.lock()->plugin_id() }
        };
        l.push_back(k);
    }
    return l;
};