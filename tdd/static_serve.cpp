#include <filesystem>
#include <fstream>
#include <iostream>

#include <ixwebsocket/IXHttpServer.h>

ix::HttpResponsePtr static_serve(std::filesystem::path frontend_dir, ix::HttpRequestPtr request,
    std::shared_ptr<ix::ConnectionState> connectionState)
{

    bool not_found = false;
    // Get Filename from URI
    auto path = request->uri.substr(1, request->uri.find_first_of('?') - 1);
    auto fpath = frontend_dir / path;
    std::cout << path << std::endl;

    if (std::filesystem::is_directory(fpath)) {
        auto a = fpath.parent_path() / (fpath.filename().string() + ".html");
        auto b = fpath / "index.html";

        if (std::filesystem::is_regular_file(a)) {
            fpath = a;
        } else if (std::filesystem::is_regular_file(b)) {
            fpath = b;
        }
    }

    if (!std::filesystem::exists(fpath) || std::filesystem::is_directory(fpath)) {
        fpath = frontend_dir / "404.html";
        not_found = true;
    }

    std::string content;
    if (std::filesystem::exists(fpath)) {
        std::ifstream t(fpath);
        t.seekg(0, std::ios::end);
        std::cout << t.tellg() << std::endl;
        content.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        content.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    } else {
        content = "File not found, additionally, a 404 document could not be found";
    }

    if (!not_found) {

        return std::make_shared<ix::HttpResponse>(200, "OK",
            ix::HttpErrorCode::Ok,
            ix::WebSocketHttpHeaders(),
            content);
    } else {
        return std::make_shared<ix::HttpResponse>(404, "NOT FOUND",
            ix::HttpErrorCode::Ok,
            ix::WebSocketHttpHeaders(),
            content);
    }
}