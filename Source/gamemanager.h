#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QPushButton>
#include <mainwindow.h>

class MainWindow;

class GameManager: public QObject
{
    Q_OBJECT
private:
    QString name;
    MainWindow * mw1 = nullptr;
    MainWindow * mw2 = nullptr;

public:
    explicit GameManager(QObject *parent = nullptr);
    void setMainWindowA (MainWindow *mw1);
    void setMainWindowB (MainWindow *mw2);
    void updateMove(int diceValue, QPushButton *VarButton);

signals:
    void clicked();

public slots:
    void sendName(QString name);
    void updateMove(int diceValue, QString BtnName);


};

#endif // GAMEMANAGER_H
