#include <iostream>
#include <json.hpp>
#include <td/json_store.hpp>
#include <td/web/manager.hpp>

#include <ixwebsocket/IXWebSocketServer.h>
#include <memory>
#include <td/web/rpc_handler.hpp>

int main(int argc, char** argv)
{
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");

    std::filesystem::path exe(argv[0]);
    auto dir = exe.parent_path().parent_path() / "plugins";
    auto frontend_dir = exe.parent_path().parent_path() / "share/td/frontend";

    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        try {
            d->add_plugin(entry.path());

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    int port = 8080;
    std::string host("0.0.0.0"); // If you need this server to be accessible on a different machine, use "0.0.0.0"
    ix::WebSocketServer server(port, host);

    td::web::rpc_handler handler(d);

    auto fn = std::bind(
        &td::web::rpc_handler::onData,
        &handler,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3);
    server.setOnClientMessageCallback(fn);

    auto res = server.listen();
    if (!res.first) {
        // Error handling
        return 1;
    }

    server.disablePerMessageDeflate();

    server.start();
    server.wait();

    return 0;
}
