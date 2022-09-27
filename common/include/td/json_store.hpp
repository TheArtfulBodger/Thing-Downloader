#pragma once
#include <filesystem>

#include <td/store.hpp>

namespace td {
/*!
 * @brief Storage class, which reads/writes a local JSON file
 * @details This is fine for storing configuration data, but should probably be avoided for secret storage
 */
class json_store : public store {
    std::filesystem::path p;

public:
    /**
     * @brief Construct a new json store object
     * @param p `std::filesystem::path` path object representing the json file
     */
    explicit json_store(std::filesystem::path p);

    std::string get(std::string& plugin, std::string& key) override;

    void set(std::string& plugin, std::string& key, std::string& value) override;

    std::vector<std::string> get_keys(std::string& plugin) override;
};
}