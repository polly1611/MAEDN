#ifndef PITCH_H
#define PITCH_H

#include <iostream>
#include <server.h>

using namespace std;

struct Field
{
    int position;
    string color;
};

class pitch
{

private:

    int mainField[40];
    int startFieldRed [4];
    int startFieldBlue[4];
    int startFieldGreen[4];
    int startFieldYellow[4];
    int finishFieldRed[4];
    int finishFieldBlue[4];
    int finishFieldGreen[4];
    int finishFieldYellow [4];

public:
    pitch();
};

#endif // PITCH_H
