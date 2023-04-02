#ifndef GYM_H
#define GYM_H
#include "ownable.h"

class Player;

class Gym : public Ownable
{
public:
    Gym(std::string name, int index, int cost);
    virtual void action(Player *p) override;
};

#endif
