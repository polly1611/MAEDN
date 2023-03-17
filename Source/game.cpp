#include "game.h"
#include "player.h"

#include <QRandomGenerator>
#include <QList>

Game *Game::m_instance = nullptr;

Game *Game::getInstance()
{
  if (m_instance == nullptr)
  {
      m_instance = new Game;
  }
  return m_instance;
}
Game::Game(QObject *parent)
    : QObject{parent}
{

}
void Game::createPlayer(QString playerId)
{
    //Spieler erstellen
    for (int i = 0; i < 4; i++) {
     if (PlayerList[i]->isEmpty()){
         Player player;
         player.playerID = playerId;

         //Vergabe der Farben
         if (i == 0){
         player.Color = Color::RED;
         } else if (i == 1){
         player.Color = Color::BLUE;
         } else if (i == 2){
         player.Color = Color::GREEN;
         } else if (i == 3){
         player.Color = Color::YELLOW;
         }

          //Erstellen der Figuren
          for (int j = 0; j < 4; j++) {
          Piece piece;
          piece.pieceID =   QUuid::createUuid().toString();
          player.PieceList[j]->append(piece);
          }
        PlayerList[i]->append(player);
        break; // Um nur einen Spieler zu erstellen
        }
    }
 }

void Game::update()
{
    // Prüfung, ob das Spielfeld bereits besetzt ist und Wurf der vorherigen Figur

    // Prüfung ob der Spieler einen weitern Zug tätigen darf
}
void Game::reset()
{
    // Spiel zurücksetzen
}
void Game:: start()
{
    // Spieler, Figuren und Häuser und Startpositionen festlegen

}
void Game::stop()
{
    //Spiel abbrechen
}
void Game::rollDice(QString playerId)
{
    //Erstellen von der gewürfelten Zahl mit Zufallsgenerator
    int value;
    value = QRandomGenerator::global()->bounded(1,7);

    qDebug() << value;

    rememberToken = QUuid::createUuid().toString(); //Token erstellen für die Server/Client Kommunikation

    qDebug() << rememberToken;

    std::map<std::string, JSONUtils::Value> data{
        {"code", 110},
        {"UUID", playerId.toStdString()},
        {"Rolled", value},
        {"rememberToken", rememberToken.toStdString()}
    };

    WebSocketServer::getInstance().sendToSocket(playerId, QString::fromStdString(JSONUtils::generateJSON(data)));


    //Ausgabe im Spielfeld in einem Textfeld fehlt noch
}
void Game::setPlayerPiecePosition(Player *Player, Piece *Piece, int Position)
{
   //Spielzug: Spieler setzt eine Spielfigur neu

}
