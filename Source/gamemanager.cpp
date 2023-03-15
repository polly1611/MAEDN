#include "gamemanager.h"

GameManager::GameManager(QObject *parent): QObject{parent}
{

}

void GameManager::setMainWindowA (MainWindow *mw1){

    // Initialisierung der Spielbretts
    this->mw1=mw1;
}
void GameManager::setMainWindowB (MainWindow *mw2){

    // Initialisierung der Spielbretts
    this->mw2=mw2;
}

void GameManager::sendName(QString name)
{
   //Name wird vom StartWindow an MainWindow weitergegeben
   mw1->sendName(name);
   mw2->sendName(name);
}

void GameManager::updateMove(int diceValue, QString BtnName)
{
    //Aufruf Spielzug-Logic und Übergabe an die Spielfelder
    mw1->move(diceValue, BtnName);
    mw2->move(diceValue, BtnName);
}
