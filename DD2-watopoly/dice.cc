#include "dice.h"
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

Dice::Dice(int die1, int die2) : die1{die1}, die2{die2} {}

int Dice::roll()
{
    isDouble = false;
    std::vector<int> dice1;
    std::vector<int> dice2;
    for (int i = 1; i <= die1; i++)
    {
        dice1.emplace_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(dice1.begin(), dice1.end(), std::default_random_engine(seed));
    for (int i = 1; i <= die2; i++)
    {
        dice2.emplace_back(i);
    }
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(dice2.begin(), dice2.end(), std::default_random_engine(seed));
    if (dice1[0] == dice2[0])
    {
        isDouble = true;
    }
    cout << "\nRolling..." << endl;
    sleep_for(seconds(1));
    cout << "First Dice: " << dice1[0] << endl;
    cout << "Second Dice: " << dice2[0] << endl;
    return (dice1[0] + dice2[0]);
}

bool Dice::getIsDouble()
{
    return isDouble;
}

