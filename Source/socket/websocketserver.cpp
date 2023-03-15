#include "websocketserver.h"


QList<QWebSocket *> WebSocketServer::m_sockets;

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    if (!m_socketServer.listen(QHostAddress::Any, port)) {
        qFatal("Failed to open web socket server.");
    }

    pmm = new PlayerCommuniManager();


    m_instance = this;

    qDebug() << "WebSocket server listening on port" << m_socketServer.serverPort();
    connect(&m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

WebSocketServer::~WebSocketServer() {
    m_socketServer.close();
    qDeleteAll(m_sockets.begin(), m_sockets.end());
}

WebSocketServer* WebSocketServer::m_instance = nullptr;

WebSocketServer& WebSocketServer::getInstance(quint16 port)
{
    if(!m_instance)
        m_instance = new WebSocketServer(port);
    return *m_instance;
}

void WebSocketServer::onNewConnection() {
    QWebSocket *socket = m_socketServer.nextPendingConnection();

    // Give every Connection an ID and send that ID to Player
    // Player will save that ID, it will act as an authentication Token
    QString playerId = QUuid::createUuid().toString().mid(1, 36).toUpper();

    qDebug() << "PlayerID: " << playerId;

    socket->setProperty("UUID", playerId);

    try {
            QueueManager::addPlayer(playerId);
        } catch (QueueFullException &e) {
            qDebug() << e.what();
        }
    std::map<std::string, JSONUtils::Value> data{
        {"code", 200},
        {"UUID", playerId.toStdString()},
        {"message", "Connection established to SocketServer!"}
    };

    Game::getInstance()->createPlayer(playerId);
    socket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));

    // Connect to the socket's signals
    connect(socket, &QWebSocket::textMessageReceived, pmm, &PlayerCommuniManager::onTextmessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);

    m_sockets.append(socket);
    // If queue is full
        if (QueueManager::getQueueSize() == 4) {     // TODO Falls noch Zeit ist prüfen, ob wir das Spiel auch mit weniger Spieler starten wollen.

            // Send the GameID to the Players
            std::map<std::string, JSONUtils::Value> data{
                {"code", 201},
                {"message", "GameID sent to Players!"},
                {"gameId", QueueManager::getGameId().toString().toStdString()}
            };

            Game::getInstance()->start();

            this->broadcast(QString::fromStdString(JSONUtils::generateJSON(data)));
        }
}

void WebSocketServer::onTextMessageReceived(QString message) {
    qDebug() << "Received message " << message;
    // This method has been deprecated.
}

void WebSocketServer::onBinaryMessageReceived(QByteArray message) {
    qDebug() << "Received binary message of size" << message.size() << "bytes";

    // Send a response back to the client
        QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
        if (senderSocket) {
            std::map<std::string, JSONUtils::Value> data{
              {"code", 202},
              {"message", "Received Binary Message!"},
              {"received_message", message.toStdString()}
            };
            senderSocket->sendBinaryMessage(QString::fromStdString(JSONUtils::generateJSON(data)).toUtf8());
        }
}

void WebSocketServer::onSocketDisconnected() {
    // Get the disconnected socket
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Disconnected one User.";

    // Remove the socket from the list of connected sockets
    m_sockets.removeOne(socket);

    // Notify Players
    std::map<std::string, JSONUtils::Value> data{
        {"code", 203},
        {"message", "One Player disconnected!"}
    };
    for (QWebSocket *socket : m_sockets) {
        socket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
    }

    // Stop Game
    Game::getInstance()->stop();

    // Disconnected all Users

    for (QWebSocket *socket : m_sockets) {
        socket->disconnect();
    }

    m_sockets.clear();

    //Reset the Queue & Game
    Game::getInstance()->reset();
    QueueManager::resetQueue();

    // Delete the socket
    socket->deleteLater();
}

void WebSocketServer::broadcast(const QString &message) {
    // Iterate over the list of connected sockets
    for (auto socket : m_sockets) {
        // Send the message to the socket
        socket->sendTextMessage(message);
    }
}
void WebSocketServer::sendToSocket(QString UUID, const QString &message){
    qDebug() << message;
     for(auto socket: m_sockets){
         qDebug() << socket->property("UUID").toString();
         qDebug() << UUID;
        if (socket->property("UUID").toString() == UUID){
            socket->sendTextMessage(message);
        }
     }
}

