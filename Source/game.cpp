#include "game.h"
#include "player.h"

#include <QRandomGenerator>

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
{}

void Game::update()
{
    // Die Prüfung, ob der Spielzug korrekt ist

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
    //Würfel
    int value;
    value = QRandomGenerator::global()->bounded(1,7);

    qDebug() << value;

    rememberToken = QUuid::createUuid().toString();

    qDebug() << rememberToken;

    std::map<std::string, JSONUtils::Value> data{
        {"code", 110},
        {"UUID", playerId.toStdString()},
        {"Rolled", value},
        {"rememberToken", rememberToken.toStdString()}
    };

    WebSocketServer::getInstance().sendToSocket(playerId, QString::fromStdString(JSONUtils::generateJSON(data)));



    //Ausgabe im Spielfeld in einem Textfeld fehlt
}
void Game::setPlayerPiecePosition(Player *Player, Piece *Piece, int Position)
{
   //Spielzug: Spieler setzt eine Spielfigur neu

}
