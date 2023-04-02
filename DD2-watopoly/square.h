#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"

class Player;
class Game;

class Square : public Subject
{
    std::string name;
    int index;

public:
    Square(std::string name, int index);
    virtual void action(Player *p);
    std::string getName();
    int getIndex();
    virtual ~Square() = 0;
};

#endif

