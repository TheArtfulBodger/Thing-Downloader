#include <td/web/rpc_functions.hpp>

void td::web::rpc_handler::populate_functions()
{
    functions["get_jobs"] = td::web::rpc::get_jobs;
}