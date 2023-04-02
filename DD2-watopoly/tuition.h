#ifndef TUITION_H
#define TUITION_H
#include "square.h"
#include "player.h"

class Tuition : public Square
{
public:
    Tuition(std::string name, int index);
    void action(Player *p) override;
};

#endif
