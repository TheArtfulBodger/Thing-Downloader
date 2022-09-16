#include <iostream>
#include <json.hpp>
#include <td/json_store.hpp>
#include <td/web/manager.hpp>

#include <memory>

#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>

struct rpc_handler : seasocks::WebSocket::Handler {

    void rpc_error(seasocks::WebSocket* sock, int code, std::string message, nlohmann::json req)
    {
        nlohmann::json err = {
            { "jsonrpc", "2.0" },
            { "error", { { "code", code }, { "message", message } } },
            { "id", req["id"] }
        };
        sock->send(err.dump());
    }

    void rpc_data(seasocks::WebSocket* sock, nlohmann::json result, nlohmann::json req)
    {
        nlohmann::json res = {
            { "jsonrpc", "2.0" },
            { "result", result },
            { "id", req["id"] }
        };
        sock->send(res.dump());
    }

    void onConnect(seasocks::WebSocket* socket) override
    {
    }

    void onData(seasocks::WebSocket* sock, const char* data) override
    {
        nlohmann::json j;
        try {
            j = nlohmann::json::parse(data);
            if (j["jsonrpc"] != "2.0") {
                throw std::runtime_error("JSON-RPC Version must be 2.0");
            }
            if (j["id"] == nullptr) {
                throw std::runtime_error("id field should not be null");
            }
            // handle method and params

            nlohmann::json l = nlohmann::json::array();
            for (auto& c : dl->get_jobs()) {
                nlohmann::json k = {
                    {"key", c.first},
                    {"value", nlohmann::json::parse(c.second->to_json())},
                    {"plugin", c.second->thin.lock()->plugin_id()}
                };
                l.push_back(k);
            }

            rpc_data(sock, l, j);
            
        } catch (nlohmann::json::parse_error&) {
            rpc_error(sock, -32700, "Parser Error", nullptr);
        } catch (std::runtime_error& e) {
            rpc_error(sock, -32600, e.what(), j);
        }
    }

    void onDisconnect(seasocks::WebSocket* socket) override
    {
    }

    rpc_handler(std::shared_ptr<td::web::downloader> dl)
        : dl(dl)
    {
    }

    std::shared_ptr<td::web::downloader> dl;
};

int main()
{
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");

    std::string apod = "./plugins/operavision/liboperavision.so";

    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    d->add_plugin(apod);
    d->get_jobs_plugin("operavision");

    seasocks::Server server(std::make_shared<seasocks::PrintfLogger>());
    server.addWebSocketHandler("/rpc", std::make_shared<rpc_handler>(d));
    server.serve(".", 9090);

    /*while (true) {
        nlohmann::json j = nlohmann::json::array();
        // d->loop_once();
        std::string word;
        std::cin >> word;
        for (auto& c : d->get_jobs()) {
            nlohmann::json k = {{"key", c.first}, {"value", nlohmann::json::parse(c.second->to_json())}};
            j.push_back(k);
        }
        std::cout << j << std::endl;
    }*/

    return 0;
}
