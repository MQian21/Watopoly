#include <sstream>
#include "player.h"
#include <string>
#include <iostream>

using namespace std;

// Static
int Player::activeCups{0};

Player::Player(Game *game, string name, char piece) : game{game}, index{0}, name{name}, piece{piece}, money{1500}, netWorth{1500}, residenceOwned{0}, gymsOwned{0}, cupsOwned{0}, jailTurns{0}, rolled{false}, calledAuction{false}, blocksOwned{map<string, int>{{"Arts1", 0}, {"Arts2", 0}, {"Eng", 0}, {"Health", 0}, {"Env", 0}, {"Sci1", 0}, {"Sci2", 0}, {"Math", 0}}}
{
}

string Player::getName()
{
    return name;
}

char Player::getPiece()
{
    return piece;
}

int Player::getIndex()
{
    return index;
}

int Player::move(int spaces)
{
    index += spaces;
    if (index >= 40)
    {
        if (index > 40)
        {
            cout << "You passed by Collect OSAP and collected $200.\n"
                 << endl;
            collect(200);
        }
        index = index % 40;
    }
    notifyObservers();
    return index;
}

// Used for SLC and moving to Jail
void Player::moveAndLand(int index)
{
    this->index = index;
    notifyObservers();
    // Take action on the square
    game->getBoard()->getSquare(index).action(this);
}

int Player::getMoney()
{
    return money;
}

void Player::pay(int amount)
{
    if (amount > netWorth) {
        throw NoMoney{true};
    }
    else if (amount > money) {
        throw NoMoney{amount - netWorth};
    }
    money -= amount;
    netWorth -= amount;
}

void Player::collect(int amount)
{
    money += amount;
    netWorth += amount;
}

void Player::addBlocksOwned(std::string blockname)
{
    blocksOwned[blockname] += 1;
}

void Player::subBlocksOwned(std::string blockname)
{
    blocksOwned[blockname] -= 1;
}

int Player::getBlocksOwned(std::string blockname)
{
    return blocksOwned[blockname];
}

int Player::getNetWorth()
{
    return netWorth;
}

void Player::addNetWorth(int amount)
{
    netWorth += amount;
}

void Player::subNetWorth(int amount)
{
    netWorth -= amount;
}

int Player::getResidenceOwned()
{
    return residenceOwned;
}

void Player::addResidenceOwned()
{
    residenceOwned++;
}

void Player::subResidenceOwned()
{
    residenceOwned--;
}

int Player::getGymsOwned()
{
    return gymsOwned;
}

void Player::addGymsOwned()
{
    gymsOwned++;
}

void Player::subGymsOwned()
{
    gymsOwned--;
}

int Player::getCupsOwned()
{
    return cupsOwned;
}

void Player::addRimCup()
{
    cupsOwned++;
}

void Player::subRimCup()
{
    cupsOwned--;
}

int Player::getActiveCups()
{
    return activeCups;
}

void Player::subActiveCups()
{
    activeCups++;
}

void Player::addActiveCups()
{
    activeCups--;
}

void Player::setJailTurns(int turns)
{
    jailTurns = turns;
}

int Player::getJailTurns()
{
    return jailTurns;
}

bool Player::getRolled()
{
    return rolled;
}

void Player::setRolled(bool state)
{
    rolled = state;
}

bool Player::getCalledAuction()
{
    return calledAuction;
}

void Player::setCalledAuction(bool state)
{
    calledAuction = state;
}

void Player::setCupsOwned(int amount) {
    cupsOwned = amount;
}

void Player::setMoney(int amount) {
    money = amount;
}

