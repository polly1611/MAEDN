#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QQueue>
#include <QUuid>
#include <QMap>

class QueueFullException : public std::exception {
public:
    /**
     * @brief Get the error message associated with the exception
     * @return The error message as a C-style string
     */
    const char* what() const throw();
};

class QueueManager
{
public:
    QueueManager();
    static void addPlayer(QString playerId);

        /**
         * @brief Remove a player from the queue
         * @param playerId The ID of the player to remove
         * @return 0 if successful, -1 if the player is not in the queue
         */
        static int removePlayer(QString playerId);


        /**
         * @brief Get the current size of the queue
         * @return The size of the queue
         */
        static int getQueueSize();

        /**
         * @brief Get the current game's ID
         * @return The game's ID
         */
        static QUuid getGameId();

        /**
         * @brief Reset the queue
         */
        static void resetQueue();

    private:
        /**
         * @var queue
         * @brief The queue of players
         */
        static QQueue<QString> queue;

        /**
         * @var games
         * @brief The games that are being played
         */
        static QMap<QUuid,QQueue<QString>> games;

        /**
         * @var gameId
         * @brief The ID of the current game
         */
        static QUuid gameId;

};

#endif // QUEUEMANAGER_H
