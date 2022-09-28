#include <td/spec/v1.hpp>

const int version = 1;
std::string key = "humble-bundle";
std::string name = "Humble Bundle";
std::string description = "Download games and downloadables from Humble Bundle";
std::vector<std::string> required_confs = {};
std::vector<std::string> required_secrets = { "_SIMPLEAUTH_SESS" };