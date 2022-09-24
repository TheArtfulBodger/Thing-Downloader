#pragma once
#include <filesystem>

#include <td/store.hpp>

namespace td {
class json_store : public store {
    std::filesystem::path p;

public:
    explicit json_store(std::filesystem::path p);

    std::string get(std::string& plugin, std::string& key) override;
    void set(std::string& plugin, std::string& key, std::string& value) override;
    std::vector<std::string> get_keys(std::string& plugin) override;
};
}