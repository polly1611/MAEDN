#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QPushButton>
#include <mainwindow.h>

class MainWindow;
class csvFile;

class GameManager: public QObject
{
    Q_OBJECT
private:
    QString name;
    MainWindow * mw1 = nullptr;
    MainWindow * mw2 = nullptr;
    csvFile * csv = nullptr;

public:
    explicit GameManager(QObject *parent = nullptr);
    void setMainWindowA (MainWindow *mw1);
    void setMainWindowB (MainWindow *mw2);
    void setCSVFile (csvFile * csv);


public slots:
    void sendName(QString name);
    void updateMove(int diceValue, QString BtnName);
    void update(QString VarButton, int oldfieldID, int diceValue);


};

#endif // GAMEMANAGER_H
