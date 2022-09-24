
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
extern rpc_t get_plugins;
extern rpc_t load_plugin;
extern rpc_t set_config;
extern rpc_t set_secret;
extern rpc_t load_jobs;

}