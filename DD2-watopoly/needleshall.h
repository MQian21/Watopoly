#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "square.h"
#include "player.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class NeedlesHall : public Square
{
public:
    NeedlesHall(std::string name, int index);
    int getChange();
    void action(Player *p) override;
};

#endif
