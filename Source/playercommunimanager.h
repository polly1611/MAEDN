#ifndef PLAYERCOMMUNIMANAGER_H
#define PLAYERCOMMUNIMANAGER_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include "utils/jsonutils.h"


// Handels the communication between players

class PlayerCommuniManager: public QObject
{
    Q_OBJECT
public:
    explicit PlayerCommuniManager(QObject *parent = nullptr);

public slots:
    void onTextmessageReceived(const QString &message);

};

#endif // PLAYERCOMMUNIMANAGER_H
