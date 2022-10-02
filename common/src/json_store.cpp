#include <fstream>

#include <td/json_store.hpp>

#include <json.hpp>

td::json_store::json_store(std::filesystem::path p)
    : p(p)
{
}

std::string td::json_store::get(std::string& plugin, std::string& key)
{

    std::ifstream f(p);
    nlohmann::json j;
    try {
        j = nlohmann::json::parse(f);

    } catch (nlohmann::json::parse_error&) {
        j = nlohmann::json::object();
    }
    f.close();

    if (!j[plugin].is_object()) {
        return "";
    }

    return j[plugin][key].get<std::string>();
}

void td::json_store::set(std::string& plugin, std::string& key, std::string& value)
{
    std::ifstream f(p);
    nlohmann::json j;
    try {
        j = nlohmann::json::parse(f);

    } catch (nlohmann::json::parse_error&) {
        j = nlohmann::json::object();
    }
    f.close();

    if (!j[plugin].is_object()) {
        j[plugin] = nlohmann::json::object();
    }

    if (value != "") {
        j[plugin][key] = value;
    } else {
        j[plugin].erase(key);
    }

    std::ofstream of(p);
    of << j.dump(2) << std::endl;
}

std::vector<std::string> td::json_store::get_keys(
    std::string& plugin)
{
    std::ifstream f(p);
    nlohmann::json j;
    try {
        j = nlohmann::json::parse(f);

    } catch (nlohmann::json::parse_error&) {
        j = nlohmann::json::object();
    }
    f.close();

    std::vector<std::string> keys;
    auto k = j[plugin];

    if (k == nullptr) {
        return std::vector<std::string>();
    }

    for (auto it = k.begin(); it != k.end(); ++it) {
        keys.push_back(it.key());
    }

    return keys;
}