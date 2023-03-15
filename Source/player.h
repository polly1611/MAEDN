#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <server.h>
#include <iostream>
#include <QList>

using namespace  std;

enum Color {
  RED, BLUE, GREEN, YELLOW
};

struct Piece {

public:
    QString pieceID;
    int fieldPosition = 0;
};

struct Player {
public:
   QString playerID;
   QList <Piece> *PieceList[4];
   Color Color;
};

#endif // PLAYER_H*/
