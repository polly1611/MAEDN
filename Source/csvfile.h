#ifndef CSVFILE_H
#define CSVFILE_H

#include <QObject>
#include <gamemanager.h>

class csvFile : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString oldfieldID;
    int diceValue;
    GameManager *gm;

public:
    explicit csvFile(QObject *parent = nullptr);
    void setGameManager (GameManager *gm);
    void update(QString VarButton, int oldfieldID, int diceValue);
};

#endif // CSVFILE_H
