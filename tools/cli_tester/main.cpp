#include <td/minimal/downloader.hpp>
#include <iostream>

#include <td.hpp>

int main(int argc, char** argv)
{
    std::cout << "ThingDownloader Plugin Tester" << std::endl;
    if (argc == 1) {
        std::cout << "Usage: td-test <FILE>\n<FILE> \t Path to the plugin file" << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    std::cout << "Loading plugin: " << path << " ... " << std::flush;
    std::shared_ptr<td::plugin> plugin;

    try {
        plugin = std::make_shared<td::plugin>(path);
    } catch (std::runtime_error& e) {
        std::cout << "\nError: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Successfully Loaded!\nPlugin is called " << plugin->name << " (" << plugin->key << ")\n"
              << std::endl;
    std::string value;
    auto downloader = std::make_shared<td::minimal_downloader>();

    // Load Variables and Secrets
    std::cout << "It Has " << plugin->required_confs.size() << " Required Configurations, we'll set them now" << std::endl;

    for (auto& conf : plugin->required_confs) {
        std::cout << conf << ": " << std::flush;
        std::getline(std::cin, value);
        downloader->set_conf(conf, value);
    }
    std::cout << std::endl;

    std::cout << "It Has " << plugin->required_secrets.size() << " Required Secrets" << std::endl;
    for (auto& secret : plugin->required_secrets) {
        std::cout << secret << ": " << std::endl;
        std::getline(std::cin, value);
        downloader->set_secret(secret, value);
    }

    std::cout << "Let's populate some queues" << std::endl;

    plugin->get_jobs(downloader);
    std::cout << "We have " << downloader->job_queue.size() << " jobs in the queue" << std::endl;

    std::cout << "Let's download some files" << std::endl;
    while (!downloader->job_queue.empty()) {
        auto job = downloader->job_queue.front();
        downloader->job_queue.pop();
        if (!plugin->should_skip(downloader, job)) {
            plugin->process_job(downloader, job);
        } else {
            std::cout << "Skipping" << std::endl;
        }
    }

    return 0;
}