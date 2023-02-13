#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <server.h>
#include <iostream>

using namespace  std;

enum Color {
  RED, BLUE, GREEN, YELLOW
};

struct Piece {
private:
    QString pieceID;
public:
    int fieldPosition;
};

struct Player {
public:
   QString playerID;
   Piece *PieceList[4];
   Color Color;
};

#endif // PLAYER_H
