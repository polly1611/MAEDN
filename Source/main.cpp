// Qt Imports
#include <QCoreApplication>
#include <QApplication>

// STD Imports
#include <iostream> // std::cout

#include <gamemanager.h>
#include <startwindow.h>
#include <mainwindow.h>



// Custom Modules
//#include "socket/websocketserver.h"
//#include "ws/webserver.h"

// WS Routes
//#include "routes/jsontestroute.h"
//#include "routes/httptestroute.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
   /* qputenv("QT_MESSAGE_PATTERN", "%{file}:%{line} %{message}");

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
    }*/

    //GameManager initialisieren
    GameManager gm;

    //Spielbretter und Anmeldefenster initialisieren
    MainWindow mw1;
    MainWindow mw2;
    StartWindow w1;
    StartWindow w2;


    //Verbindungsaufbau zum Model
    mw1.setGameManager(&gm);
    mw2.setGameManager(&gm);
    w1.setGameManager(&gm);
    w2.setGameManager(&gm);


    //Verbindungsaufbau vom Model zu den Spielbrettern und Datenbanken
    gm.setMainWindowA(&mw1);
    gm.setMainWindowB(&mw2);

    //Aufruf der Spielbretter und Anmeldefenster
    mw2.show();
    w2.show();
    mw1.show();
    w1.show();

    return a.exec();
}
