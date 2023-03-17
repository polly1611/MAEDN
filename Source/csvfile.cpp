#include "csvfile.h"

csvFile::csvFile(QObject *parent):QObject {parent}
{

}

void csvFile::setGameManager (GameManager *gm)
{
    //Verbindung zum GameManager aufbauen;
    this ->gm = gm;
}

void csvFile::update(QString VarButton, int oldfieldID, int diceValue)
{

}
