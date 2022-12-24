#include <filesystem>
#include <fstream>

#include <ixwebsocket/IXHttpServer.h>

ix::HttpResponsePtr static_serve(std::filesystem::path frontend_dir, ix::HttpRequestPtr request,
    std::shared_ptr<ix::ConnectionState> connectionState)
{
    // Get Filename from URI
    auto path = request->uri.substr(1, request->uri.find_first_of('?') -1);
    auto fpath = frontend_dir / path;

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
    }

    std::string content;
    {
        std::ifstream t(fpath);
        t.seekg(0, std::ios::end);
        content.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        content.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    }

    return std::make_shared<ix::HttpResponse>(200, "OK",
        ix::HttpErrorCode::Ok,
        ix::WebSocketHttpHeaders(),
        content);
}