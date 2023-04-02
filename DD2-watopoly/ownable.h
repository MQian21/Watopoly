#ifndef OWNABLE_H
#define OWNABLE_H
#include "square.h"

class Player;

class Ownable : public Square
{
    int cost;
    Player *owner;
    bool isMortgaged;

public:
    Ownable(std::string name, int index, int cost);
    Player *getOwner();
    bool getIsMortgaged();
    bool buyProperty(Player *p);
    void setOwner(Player *p);
    int getCost();
    virtual ~Ownable() = 0;
    void setMortgaged(bool state);
};

#endif
