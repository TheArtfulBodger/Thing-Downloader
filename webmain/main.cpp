#include <iostream>
#include <td/json_store.hpp>
#include <td/web/manager.hpp>

int main()
{
    td::store_t secrets = std::make_shared<td::json_store>("secrets.json");
    td::store_t conf = std::make_shared<td::json_store>("conf.json");

    std::string apod = "./plugins/operavision/liboperavision.so";

    std::filesystem::path p(".");

    auto d = std::make_shared<td::web::downloader>(6, p, secrets, conf);

    d->add_plugin(apod);
    d->get_jobs_plugin("operavision");

    while (true) {
        // d->loop_once();
        std::string word;
        std::cin >> word;
        std::cout << word << std::endl;
    }

    return 0;
}