#pragma once
#include <memory>
#include <string>
#include <vector>

namespace td {

/*! @brief abstract class for storing configs & secrets */
class store : public std::enable_shared_from_this<store> {
public:
    /**
     * @brief gets a stored value, defaulting to `""` (an empty string)
     *
     * @param plugin `std::string` the plugin the data applies to
     * @param key `std::string` the key to look up
     * @return `std::string` the stored value
     */
    virtual std::string get(std::string& plugin, std::string& key) = 0;

    /**
     * @brief Stores a value at the key
     *
     * @param plugin `std::string` the plugin the data applies to
     * @param key `std::string` the key to look up
     * @param value `std::string` the value to store
     */
    virtual void set(std::string& plugin, std::string& key, std::string& value) = 0;

    /**
     * @brief Gets the stored keys
     *
     * @param plugin `std::string` the plugin the data applies to
     * @return `std::vector<std::string>` a list of the stored keys
     */
    virtual std::vector<std::string> get_keys(std::string& plugin) = 0;
};

using store_t = std::shared_ptr<store>;
};