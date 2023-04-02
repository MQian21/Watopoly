#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Dice
{
public:
    int die1;
    int die2;
    bool isDouble;
    Dice(int die1, int die2);
    int roll();
    bool getIsDouble();
};

#endif

