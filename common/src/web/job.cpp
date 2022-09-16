#include <json.hpp>
#include <td/web/job.hpp>

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

    nlohmann::json j = {
        { "data", nlohmann::json::parse(data) },
        { "status", to_string(job_state) },
        { "progress", progress },
        { "status", status }
    };

    return j.dump();
}