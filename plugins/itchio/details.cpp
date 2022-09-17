#include <td/spec/v1.hpp>

const int version = 1;
std::string key = "itchio";
std::string name = "Itch.Io";
std::string description = "Download games and downloadables from itch.io";
std::vector<std::string> required_confs = {};
std::vector<std::string> required_secrets = { "API_KEY" };