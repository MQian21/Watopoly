#ifndef GOTIMS_H
#define GOTIMS_H
#include "player.h"
#include "square.h"

class GoTims : public Square
{
public:
    GoTims(std::string name, int index);
    void action(Player *p) override;
};

#endif
