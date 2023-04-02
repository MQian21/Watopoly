#include "residence.h"
#include <string>
#include <vector>
#include "iostream"
#include "player.h"
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

Residence::Residence(string name, int index, int cost) : Ownable{name, index, cost,} {}

void Residence::action(Player *p)
{
    cout << "You landed on " << getName() << "!" << endl;
    if (getOwner() == p)
    {
        cout << "This is your residence. What would you like to do now?" << endl;
    }
    else if (getOwner() == nullptr)
    {
        string cmd;
        cout << "This residence has not been bought yet." << endl;
        cout << "Would you like to buy it for $" << getCost() << "? (Y/N) " << endl;
        cin >> cmd;
        if (cmd == "Y" || cmd == "y")
        {
            bool bought = buyProperty(p);
            if (bought)
            {
                p->addNetWorth(getCost());
                p->addResidenceOwned();
            }
        }
        else if (cmd == "N" || cmd == "n")
        {
            // auction(this);
            cout << "Auctioning..." << endl;
        }
    }
    else if (getOwner() != p)
    {
        cout << "This residence belongs to " << getOwner()->getName() << "!" << endl;
        int fee = 0;
        if (getOwner()->getResidenceOwned() == 1)
        {
            fee = 25;
        }
        else if (getOwner()->getResidenceOwned() == 2)
        {
            fee = 50;
        }
        else if (getOwner()->getResidenceOwned() == 3)
        {
            fee = 100;
        }
        else if (getOwner()->getResidenceOwned() == 4)
        {
            fee = 200;
        }
        cout << "You owe " << getOwner()->getName() << " $" << fee << ".\n"
             << endl;
        cout << "Paying..." << endl;
        sleep_for(seconds(1));
        p->pay(fee);
        getOwner()->collect(fee);
        cout << "You paid $" << fee << ". What would you like to do now?" << endl;
    }
}

