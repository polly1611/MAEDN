#include "playercommunimanager.h"
#include "game.h"
#include "player.h"


PlayerCommuniManager::PlayerCommuniManager(QObject *parent)
    : QObject{parent}
{

}
void PlayerCommuniManager::onTextmessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    QString playerId;

    switch (jsonObject["code"].toInt()) {
        case 110:
            // Roll Dice
            playerId = jsonObject["player"].toString();

            qDebug() << "Method 110 called";
            Game::getInstance()->rollDice(playerId);

            /*
            //Gets: player.ID
             for(auto PlayerId: Game::getInstance()->PlayerList)
             {
               if (playerId == PlayerId->playerID){
               Game::getInstance()->rollDice(playerId);

              }
              }
              */

        case 120: //Move Piece
             // Gets: playerID, rememberToken
             for(auto Player: Game::getInstance()->PlayerList){
             }

        break;
        default:
            qDebug() << message;
        break;
    }
}

