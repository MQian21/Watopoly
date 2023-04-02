#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include "square.h"

class GooseNesting : public Square
{
public:
    GooseNesting(std::string name, int index);
    void action(Player *p) override;
};

#endif
