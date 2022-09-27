#include <td/web/rpc_functions.hpp>

td::web::rpc_t td::web::rpc::get_active_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& /* params */) {
    nlohmann::json l = nlohmann::json::array();
    for (auto& c : dl->get_active_jobs()) {
        nlohmann::json k = nlohmann::json::parse(c.second->to_json());
        l.push_back(k);
    }
    return l;
};

td::web::rpc_t td::web::rpc::get_queued_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& /* params */) {
    nlohmann::json l = nlohmann::json::array();

    auto q = dl->get_job_queue();
    while (!q.empty()) {
        nlohmann::json k = nlohmann::json::parse(q.front()->to_json());
        l.push_back(k);
        q.pop();
    }
    return l;
};

auto get_paged = [](std::function<std::vector<td::web::job_t>(std::shared_ptr<td::web::downloader>)> fn) {
    return [fn](std::shared_ptr<td::web::downloader> dl, nlohmann::json& params) {
        int page;

        if (params["page"].is_null()) {
            page = 1;
        } else if (params["page"].is_number_integer()) {
            page = params["page"].get<int>();
        } else {
            throw std::make_pair(td::web::invalid_params, std::string("page in params should be int or null, got: ") + params["page"].type_name());
        }

        nlohmann::json l = nlohmann::json::array();
        auto js = fn(dl);
        for (int i = (page - 1) * 50; i < (page * 50) && i < js.size(); i++) {
            nlohmann::json k = nlohmann::json::parse(js[i]->to_json());
            l.push_back(k);
        }
        return l;
    };
};

td::web::rpc_t td::web::rpc::get_failed_jobs = get_paged([](std::shared_ptr<td::web::downloader> dl) { return dl->get_failed_jobs(); });
td::web::rpc_t td::web::rpc::get_completed_jobs = get_paged([](std::shared_ptr<td::web::downloader> dl) { return dl->get_completed_jobs(); });
td::web::rpc_t td::web::rpc::get_skipped_jobs = get_paged([](std::shared_ptr<td::web::downloader> dl) { return dl->get_skipped_jobs(); });

td::web::rpc_t td::web::rpc::get_n_failed_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& /* params */) {
    return dl->get_failed_jobs().size();
};

td::web::rpc_t td::web::rpc::get_n_completed_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& /* params */) {
    return dl->get_completed_jobs().size();
};

td::web::rpc_t td::web::rpc::get_n_skipped_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& /* params */) {
    return dl->get_skipped_jobs().size();
};

td::web::rpc_t td::web::rpc::load_jobs = [](std::shared_ptr<downloader> dl, nlohmann::json& p) {
    if (!p["plugin"].is_string()) {
        throw std::make_pair(td::web::invalid_params, std::string("plugin in params should be string: ") + p["plugin"].type_name());
    }

    std::string plugin = p["plugin"].get<std::string>();

    auto j = nlohmann::json::parse(dl->plugin_to_json(plugin));

    if (!j["has_required_confs"].get<bool>() || !j["has_required_secrets"].get<bool>()) {
        throw std::make_pair(td::web::runtime_error, "Plugin is missing configuration or secrets");
    }

    dl->get_jobs_plugin(plugin);

    return nlohmann::json { { "success", true } };
};