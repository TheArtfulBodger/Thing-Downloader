/*
#include <memory>

#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>

using namespace std;
using namespace seasocks;

struct chat_handler : WebSocket::Handler {

    set<WebSocket*> connections;

    void onConnect(WebSocket* socket) override
    {
        connections.insert(socket);
    }

    void onData(WebSocket*, const char* data) override
    {
        for (auto* c : connections)
            c->send(data);
    }

    void onDisconnect(WebSocket* socket) override
    {
        connections.erase(socket);
    }
};

int main()
{
    Server server(make_shared<PrintfLogger>());
    server.addWebSocketHandler("/chat", make_shared<chat_handler>());
    server.serve(".", 9090);

    return 0;
}
*/