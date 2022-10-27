#include <iostream>

#include <td/json_store.hpp>
#include <td/web/manager.hpp>

#include <ixwebsocket/IXHttpServer.h>
#include <ixwebsocket/IXNetSystem.h>
#include <memory>
#include <td/web/rpc_handler.hpp>

#include <windows.h>
#include <shellapi.h>


ix::HttpResponsePtr static_serve(std::filesystem::path, ix::HttpRequestPtr, std::shared_ptr<ix::ConnectionState>);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    ix::initNetSystem();
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");
    std::string s(' ', MAX_PATH);

    size_t sz = GetModuleFileNameA(nullptr, s.data(), MAX_PATH);

    std::filesystem::path exe(s.c_str());
    auto dir = exe.parent_path().parent_path() / "plugins";
    auto frontend_dir = exe.parent_path().parent_path() / "share/td/frontend";

    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        try {
            if (entry.path().extension() == ".dll") {
            d->add_plugin(std::filesystem::absolute(entry.path()).string());
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    int port = 8080;
    std::string host("0.0.0.0");
    ix::HttpServer server(port, host);

    td::web::rpc_handler handler(d);

    server.setOnClientMessageCallback(std::bind(
        &td::web::rpc_handler::onData,
        &handler,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3));

    server.setOnConnectionCallback(
        std::bind(
            static_serve,
            frontend_dir,
            std::placeholders::_1,
            std::placeholders::_2));

    auto res = server.listen();
    if (!res.first) {
        std::cout << res.second << std::endl;
        // Error handling
        return 1;
    }

    server.disablePerMessageDeflate();

    server.start();

    // Open web browser
    ShellExecuteA(0, 0, "http://localhost:8080", 0, 0 , SW_SHOW );

    // Create Notification Area Icon

    
    server.wait();

    ix::uninitNetSystem();
    return 0;
}
