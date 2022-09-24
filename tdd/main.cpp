#include <iostream>
#include <json.hpp>
#include <td/json_store.hpp>
#include <td/web/manager.hpp>

#include <memory>

#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>

#include <td/web/rpc_handler.hpp>

int main(int argc, char** argv)
{
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");

    std::filesystem::path exe(argv[0]);
    auto dir = exe.parent_path().parent_path() / "plugins";
    
    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        try {
            d->add_plugin(entry.path());

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    seasocks::Server server(std::make_shared<seasocks::PrintfLogger>(seasocks::Logger::Level::Warning));
    server.addWebSocketHandler("/rpc", std::make_shared<td::web::rpc_handler>(d));
    server.serve("/usr/share/td/frontend", 8080);

    return 0;
}
