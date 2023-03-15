#include "queuemanager.h"
#include <QDebug>

QQueue<QString> QueueManager::queue;
QMap<QUuid,QQueue<QString>> QueueManager::games;
QUuid QueueManager::gameId;

const char* QueueFullException::what() const throw() {
    return "Queue is full";
}

QueueManager::QueueManager()
{}
void QueueManager::addPlayer(QString playerId)
{
    if(queue.size()<4)
    {
        queue.enqueue(playerId);
        qDebug() << "Added Player " << playerId << " to Queue";
    }
    else
    {
        // handle case when the queue is full
        throw QueueFullException();
        return;
    }

    if((queue.size() == 4))
    {
        gameId = QUuid::createUuid();
        games[gameId] = queue;
    }
}
int QueueManager::removePlayer(QString playerId)
{
    if (!queue.isEmpty())
    {
        int index = queue.indexOf(playerId);
        if(index != -1)
        {
            queue.removeAt(index);
            return 0;
        }
        else
        {
            // handle case when the player is not in the queue
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int QueueManager::getQueueSize()
{
    return queue.size();
}

QUuid QueueManager::getGameId()
{
    return gameId;
}
void QueueManager::resetQueue()
{
    queue.clear();
}
