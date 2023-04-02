#include "ownable.h"
#include <string>
#include "player.h"
#include "square.h"

using namespace std;

Ownable::Ownable(string name, int index, int cost) : Square{name, index}, cost{cost}, owner{nullptr}, isMortgaged{false}
{
}

Player *Ownable::getOwner()
{
    return owner;
}

bool Ownable::getIsMortgaged()
{
    return isMortgaged;
}

int Ownable::getCost()
{
    return cost;
}

bool Ownable::buyProperty(Player *p)
{
    //EXCEPTIONNNNN??
    if (cost <= p->getMoney())
    {
        p->pay(cost);
        setOwner(p);
    }
    cout << "\nYou just bought the property! " << endl;
    cout << "You now have $" << p->getMoney() << "." << endl;
    return true;
}

void Ownable::setOwner(Player *p)
{
    if (owner == nullptr)
    {
        owner = p;
    }
    else if (owner != nullptr)
    {
        owner->subNetWorth(cost);
        owner = p;
        p->addNetWorth(cost);
    }
}

Ownable::~Ownable() {}

void Ownable::setMortgaged(bool state)
{
    isMortgaged = state;
}


