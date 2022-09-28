#include <json.hpp>
#include <td/spec/v1.hpp>

bool should_skip(const td::dl& base, const td::job& job)
{

    auto data = nlohmann::json::parse(job->get_job_data());

    // Probably a steam key, skip
    if (data["downloads"].empty()) {
        return true;
    }


    for (auto dl : data["downloads"]) {
        auto p = std::filesystem::path(base->get_outpath_folder()) / data["parent"]["human_name"].get<std::string>() / data["human_name"].get<std::string>();

        std::filesystem::create_directories(p);
        int n = dl["download_struct"].size();
        int i = 0;

        for (auto g : dl["download_struct"]) {
            std::string url = g["url"]["web"].get<std::string>();
            std::string rg = url.substr(0, url.find_first_of('?'));
            std::string file = rg.substr(rg.find_last_of('/') + 1);

            auto of = p / file;

            if(!std::filesystem::exists(of)){
                return false;
                // check for md5 or sha-1 file
            }
        }}


    return true;
}