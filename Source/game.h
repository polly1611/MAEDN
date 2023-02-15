#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QList>
#include <player.h>

#include "socket/websocketserver.h"


class Game : public QObject
{
    Q_OBJECT

private:
    explicit Game(QObject *parent = nullptr);
    static Game *m_instance;
    QString rememberToken;


public:
    QList <Player> *PlayerList[4];
    void update();
    void reset();
    void start();
    void stop();
    void rollDice(QString playerId);
    void createPlayer(QString playerId);
    void setPlayerPiecePosition(Player *Player, Piece *Piece, int Position);
    static Game* getInstance();

signals:

};

#endif // GAME_H
