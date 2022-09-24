#include <iostream>
#include <json.hpp>
#include <td/web/job.hpp>
#include <td/web/manager.hpp>

std::string to_string(td::web::state& st)
{
    switch (st) {
    case td::web::unprocessed:
        return "_unprocessed";
    case td::web::skipped:
        return "_skipped";
    case td::web::downloading:
        return "_downloading";
    case td::web::completed:
        return "_completed";
    case td::web::failed:
        return "_failed";
    default:
        return "_unknown";
    }
}

std::string td::web::job::to_json()
{
    auto p = thin.lock()->plugin_id();

    nlohmann::json j = {
        { "name", name },
        //{ "data", nlohmann::json::parse(data) },
        { "status", to_string(job_state) },
        { "progress", progress },
        { "log", status },
        { "plugin", p }
    };

    return j.dump();
}