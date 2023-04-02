#include "gym.h"
#include <string>
#include <iostream>
#include "player.h"
#include <chrono>
#include <thread>
#include "dice.h"
using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

Gym::Gym(string name, int index, int cost) : Ownable{name, index, cost} {}

void Gym::action(Player *p)
{
    cout << "You landed on " << getName() << "!" << endl;
    if (getOwner() == p)
    {
        cout << "This is your gym. What would you like to do now?" << endl;
    }
    else if (getOwner() == nullptr)
    {
        string cmd;
        cout << "This gym has not been bought yet." << endl;
        cout << "Would you like to buy it for $" << getCost() << "? (Y/N) " << endl;
        cin >> cmd;
        if (cmd == "Y" || cmd == "y")
        {
            bool bought = buyProperty(p);
            if (bought)
            {
                p->addNetWorth(getCost());
                p->addGymsOwned();
            }
        }
        else if (cmd == "N" || cmd == "n")
        {
            cout << "Auctioning..." << endl;
            p->setCalledAuction(true);
        }
    }
    else if (getOwner() != p)
    {
        cout << "This gym belongs to " << getOwner()->getName() << "!" << endl;
        cout << "Let's roll the dice too see how much you owe."
             << endl;
        Dice d = Dice{6, 6};
        int roll = d.roll();
        int fee = 0;
        if (getOwner()->getGymsOwned() == 1)
        {
            fee = roll * 4;
        }
        else if (getOwner()->getGymsOwned() == 2)
        {
            fee = roll * 10;
        }
        cout << "You owe " << getOwner()->getName() << " $" << fee << endl;
        cout << "\nPaying..." << endl;
        sleep_for(seconds(1));
        p->pay(fee);
        getOwner()->collect(fee);
        cout << "You paid $" << fee << ". What would you like to do now?" << endl;
    }
}

