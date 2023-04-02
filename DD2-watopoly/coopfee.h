#ifndef COOPFEE_H
#define COOPFEE_H
#include "square.h"
#include "player.h"

class CoopFee : public Square
{
public:
    CoopFee(std::string name, int index);
    void action(Player *p) override;
};

#endif

