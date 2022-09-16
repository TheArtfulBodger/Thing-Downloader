#pragma once

#include <json.hpp>

inline const int download_mode_video = 1;
inline const int download_mode_desc = 2;

struct opera {
    std::string name;
    std::string slug;
    std::string video_id;
    std::string company;
    int operation;
};

inline void to_json(nlohmann::json& j, const opera& p)
{
    j = nlohmann::json {
        { "name", p.name },
        { "slug", p.slug },
        { "video_id", p.video_id },
        { "company", p.company },
        { "operation", p.operation }
    };
}

inline void from_json(const nlohmann::json& j, opera& p)
{
    j.at("name").get_to(p.name);
    j.at("slug").get_to(p.slug);
    j.at("video_id").get_to(p.video_id);
    j.at("company").get_to(p.company);
    j.at("operation").get_to(p.operation);
}