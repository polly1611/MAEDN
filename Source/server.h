#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <iostream>

using namespace std;

class server
{
   private:
   string player[4];

public:
    server();
    void initPlayer();
    void initPitch();
};

#endif // SERVER_H
