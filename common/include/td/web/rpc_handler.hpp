#pragma once

#include <functional>
#include <json.hpp>
#include <seasocks/Server.h>
#include <unordered_map>

#include <td/web/manager.hpp>

namespace td::web {

typedef std::function<nlohmann::json(std::shared_ptr<downloader>, nlohmann::json&)> rpc_t;

enum rpc_error {
    parse_error = -32700,
    invalid_request = -32600,
    method_not_found = -32601,
    invalid_params = -32602,
    internal_error = -32603,
    /* -32000 to -32099	Server error	Reserved for implementation-defined server-errors. */
};

struct rpc_handler : seasocks::WebSocket::Handler {

    void onConnect(seasocks::WebSocket* socket) override;

    void onData(seasocks::WebSocket* sock, const char* data) override;

    void onDisconnect(seasocks::WebSocket* socket) override;

    explicit rpc_handler(std::shared_ptr<td::web::downloader> dl);

private:
    std::shared_ptr<td::web::downloader> dl;
    std::unordered_map<std::string, rpc_t> functions;
    void populate_functions();
};

}