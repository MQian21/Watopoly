#ifndef SLC_H
#define SLC_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "square.h"
#include "player.h"

class SLC : public Square
{
public:
    SLC(std::string name, int index);
    int getMove();
    void action(Player *p) override;
};

#endif
