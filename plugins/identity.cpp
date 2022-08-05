#include <v1.hpp>

const int version = 1;
std::string key = "id";
std::string name = "Identity Plugin";
std::string description = "Test for plugin example";
std::vector<std::string> required_confs = {};
std::vector<std::string> required_secrets = {};

void get_jobs(const td::dl& /*base*/)
{
    // call dl->add_job(buffer) as required;
}

void process_job(const td::dl& /*base*/, const td::job& job)
{
    std::string data = "\xafNot Implemented";
    job->set_complete(td::buffer(data.begin(), data.end()), true);
}

bool should_skip(const td::dl& /*base*/, const td::job& /*buf*/)
{
    return true;
}