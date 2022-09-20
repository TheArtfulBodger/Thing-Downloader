#include <iostream>
#include <json.hpp>
#include <td/json_store.hpp>
#include <td/web/manager.hpp>

#include <memory>

#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>

#include <td/web/rpc_handler.hpp>

int main()
{
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");

    std::string apod = "/usr/plugins/liboperavision.so";

    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    d->add_plugin(apod);
    d->get_jobs_plugin("operavision");

    seasocks::Server server(std::make_shared<seasocks::PrintfLogger>(seasocks::Logger::Level::Warning));
    server.addWebSocketHandler("/rpc", std::make_shared<td::web::rpc_handler>(d));
    server.serve("/usr/share/td/frontend", 9090);

    return 0;
}
