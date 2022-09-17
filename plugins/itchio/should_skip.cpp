#include <filesystem>
#include <iostream>

#include <json.hpp>
#include <td/spec/v1.hpp>

bool should_skip(const td::dl& base, const td::job& job)
{
    return true;
}

void load_games(const td::dl& base, const td::job& job);
void download_game(const td::dl& base, const td::job& job);

void process_job(const td::dl& base, const td::job& job)
{
}