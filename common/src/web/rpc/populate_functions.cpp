#include <td/web/rpc_functions.hpp>

void td::web::rpc_handler::populate_functions()
{
    functions["get_active_jobs"] = td::web::rpc::get_active_jobs;
    functions["get_queued_jobs"] = td::web::rpc::get_queued_jobs;
    functions["get_completed_jobs"] = td::web::rpc::get_completed_jobs;
    functions["get_failed_jobs"] = td::web::rpc::get_failed_jobs;
    functions["get_skipped_jobs"] = td::web::rpc::get_skipped_jobs;
    functions["get_n_completed_jobs"] = td::web::rpc::get_n_completed_jobs;
    functions["get_n_failed_jobs"] = td::web::rpc::get_n_failed_jobs;
    functions["get_n_skipped_jobs"] = td::web::rpc::get_n_skipped_jobs;
}