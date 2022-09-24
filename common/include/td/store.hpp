#pragma once
#include <memory>
#include <string>
#include <vector>

namespace td {

/*! @brief abstract class for storing configs & secrets */
class store : public std::enable_shared_from_this<store> {
public:
    virtual std::string get(std::string& plugin, std::string& key) = 0;
    virtual void set(std::string& plugin, std::string& key, std::string& value) = 0;

    virtual std::vector<std::string> get_keys(std::string& plugin) = 0;
};

using store_t = std::shared_ptr<store>;
};