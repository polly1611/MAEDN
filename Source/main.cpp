// Qt Imports
#include <QCoreApplication>

// STD Imports
#include <iostream> // std::cout

// Custom Modules
#include "socket/websocketserver.h"
#include "ws/webserver.h"

// WS Routes
#include "routes/jsontestroute.h"
#include "routes/httptestroute.h"

// Game
#include <server.h>

// Window
#include <mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qputenv("QT_MESSAGE_PATTERN", "%{file}:%{line} %{message}");

    // Create WebSocket Server instance
    WebSocketServer::getInstance(1214);

    // Create WebServer instance
    HttpServer server;

    // Add Route
    server.addRoute("/json", "GET", new JSONTestRoute());
    server.addRoute("/http", "GET", new HTTPTestRoute());

    // Start server on port 8080
    if (!server.start(8080)) {
        // If server failed to start, print error and exit
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    return a.exec();
    return app.exec();
}
