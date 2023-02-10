#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <player.h>

class Game : public QObject
{
    Q_OBJECT

private:
    explicit Game(QObject *parent = nullptr);
    static Game *m_instance;
    Player *PlayerList[4];

public:
    void update();
    void reset();
    void start();
    void stop();
    int rollDice();
    void setPlayerPiecePosition(Player *Player, Piece *Piece, int Position);
    static Game* getInstance();

signals:

};

#endif // GAME_H
