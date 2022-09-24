#include <td/web/rpc_functions.hpp>

td::web::rpc_t td::web::rpc::get_plugins = [](std::shared_ptr<downloader> dl, nlohmann::json& /*params*/) {
    nlohmann::json l;
    l["loaded"] = nlohmann::json::object();
    for (auto& c : dl->get_plugins()) {
        std::string k = c.first;
        l["loaded"][c.first] = nlohmann::json::parse(dl->to_json(k));
    }
    return l;
};

td::web::rpc_t td::web::rpc::load_plugin = [](std::shared_ptr<downloader> dl, nlohmann::json& params) {
    if (!params["plugin"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("plugin in params should be string: ") + params["plugin"].type_name());
    }
    try {
        dl->add_plugin(params["plugin"].get<std::string>());
        return nlohmann::json { { "success", true } };
    } catch (std::runtime_error& e) {
        throw std::make_pair(td::web::runtime_error, e.what());
    }
};

td::web::rpc_t td::web::rpc::set_secret = [](std::shared_ptr<downloader> dl, nlohmann::json& p) {
    if (!p["plugin"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("plugin in params should be string: ") + p["plugin"].type_name());
    }
    if (!p["key"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("key in params should be string: ") + p["key"].type_name());
    }
    if (!p["value"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("key in params should be string: ") + p["value"].type_name());
    }

    std::string plugin = p["plugin"].get<std::string>();
    std::string key = p["key"].get<std::string>();
    std::string value = p["value"].get<std::string>();

    dl->secrets_set(
        plugin,
        key,
        value);

    return nlohmann::json { { "success", true } };
};

td::web::rpc_t td::web::rpc::set_config = [](std::shared_ptr<downloader> dl, nlohmann::json& p) {
    if (!p["plugin"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("plugin in params should be string: ") + p["plugin"].type_name());
    }
    if (!p["key"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("key in params should be string: ") + p["key"].type_name());
    }
    if (!p["value"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("key in params should be string: ") + p["value"].type_name());
    }

    std::string plugin = p["plugin"].get<std::string>();
    std::string key = p["key"].get<std::string>();
    std::string value = p["value"].get<std::string>();

    dl->confs_set(
        plugin,
        key,
        value);

    return nlohmann::json { { "success", true } };
};