#include <td/web/rpc_handler.hpp>

td::web::rpc_handler::rpc_handler(std::shared_ptr<td::web::downloader> dl)
    : dl(dl)
{
    populate_functions();
}

void td::web::rpc_handler::onConnect(seasocks::WebSocket* socket) { }
void td::web::rpc_handler::onDisconnect(seasocks::WebSocket* socket) { }

void td::web::rpc_handler::onData(seasocks::WebSocket* socket, const char* data)
{
    nlohmann::json j;
    try {
        try {
            j = nlohmann::json::parse(data);
        } catch (nlohmann::json::parse_error&) {
            throw std::make_pair(parse_error, "Parser Error");
        }

        if (j["jsonrpc"] != "2.0") {
            throw std::make_pair(invalid_request, "JSON-RPC Version must be 2.0");
        }

        if (j["id"] == nullptr) {
            throw std::make_pair(invalid_request, "id field should not be null");
        }

        if (!j["method"].is_string()) {
            throw std::make_pair(invalid_request, std::string("method should be string, got: ") + j["method"].type_name());
        }

        std::string method = j["method"].get<std::string>();
    
            if(functions.find(method) == functions.end()){
            throw std::make_pair(method_not_found, std::string("method not found: ") +method);
            }

            rpc_t f = functions[method];

            nlohmann::json result = f(dl, j["params"]);

            nlohmann::json res = {
                { "jsonrpc", "2.0" },
                { "result", result },
                { "id", j["id"] }
            };
            socket->send(res.dump());

        
    } catch (std::pair<td::web::rpc_error, std::string>& p) {
        nlohmann::json err = {
            { "jsonrpc", "2.0" },
            { "error", { { "code", static_cast<int>(p.first) }, { "message", p.second } } },
            { "id", j["id"] }
        };
        socket->send(err.dump());
    } catch (std::pair<td::web::rpc_error, char const*>& p) {
        nlohmann::json err = {
            { "jsonrpc", "2.0" },
            { "error", { { "code", static_cast<int>(p.first) }, { "message", p.second } } },
            { "id", j["id"] }
        };
        socket->send(err.dump());
    }
}
