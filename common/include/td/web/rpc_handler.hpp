#pragma once

#include <functional>
#include <ixwebsocket/IXWebSocketServer.h>
#include <json.hpp>
#include <unordered_map>

#include <td/web/manager.hpp>

namespace td::web {

using rpc_t = std::function<nlohmann::json(std::shared_ptr<downloader>, nlohmann::json&)>;

enum rpc_error {
    parse_error = -32700,
    invalid_request = -32600,
    method_not_found = -32601,
    invalid_params = -32602,
    internal_error = -32603,

    runtime_error = -32000,
    /* -32000 to -32099	Server error	Reserved for implementation-defined server-errors. */
};

/**
 * @brief Handler type for RPC websockets, inherits from seasocks base type.
 *
 */
struct rpc_handler {

    /**
     * @brief handles a request sent, as a json_rpc request
     *
     * @param sock the websockets object
     * @param data the data sent, as a C-Style string
     */
    void onData(
        std::shared_ptr<ix::ConnectionState>,
        ix::WebSocket&,
        const ix::WebSocketMessagePtr&);

    /**
     * @brief Construct a new rpc handler object
     *
     * @param dl pointer to the downloader object
     */
    explicit rpc_handler(std::shared_ptr<td::web::downloader> dl);

private:
    std::shared_ptr<td::web::downloader> dl;
    std::unordered_map<std::string, rpc_t> functions;
    void populate_functions();
};

}