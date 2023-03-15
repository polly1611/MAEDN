#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QQueue>
#include <QUuid>
#include <QMap>

class QueueFullException : public std::exception {
public:

     // Get the error message associated with the exception
     // The error message as a C-style string

    const char* what() const throw();
};

class QueueManager
{
public:
    QueueManager();
    static void addPlayer(QString playerId);


         // Remove a player from the queue
         // playerId The ID of the player to remove
         // return 0 if successful, -1 if the player is not in the queue

        static int removePlayer(QString playerId);



         //return The size of the queue

        static int getQueueSize();


         //return The game's ID

        static QUuid getGameId();


         // Reset the queue

        static void resetQueue();

    private:

         // The queue of players

        static QQueue<QString> queue;


        //brief The games that are being played

        static QMap<QUuid,QQueue<QString>> games;


        // The ID of the current game

        static QUuid gameId;

};

#endif // QUEUEMANAGER_H
