
#include <td/web/rpc_handler.hpp>

namespace td::web::rpc {

extern rpc_t get_active_jobs;
extern rpc_t get_queued_jobs;
extern rpc_t get_completed_jobs;
extern rpc_t get_n_completed_jobs;
extern rpc_t get_failed_jobs;
extern rpc_t get_n_failed_jobs;
extern rpc_t get_skipped_jobs;
extern rpc_t get_n_skipped_jobs;

}