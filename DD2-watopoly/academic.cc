#include "academic.h"
#include <string>
#include <vector>
#include <map>
#include "square.h"
#include <iostream>
#include <thread>
#include <iostream>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

map<string, int> Academic::monopolyBlock = {
    {"Arts1", 2}, {"Arts2", 3}, {"Eng", 3}, {"Health", 3}, {"Env", 3}, {"Sci1", 3}, {"Sci2", 3}, {"Math", 2}};

Academic::Academic(std::string name, int index, int cost, int improvementCost, string blockKey, vector<int> improvementTuition) : Ownable{name, index, cost}, improvementCost{improvementCost}, improvementCount{0}, blockKey{blockKey}, improvementTuition{improvementTuition}
{
}

void Academic::action(Player *p)
{
    cout << "You landed on " << getName() << "!\n"
         << endl;

    if (getOwner() == p)
    {
        cout << "This is your property and it is";
        if (getIsMortgaged())
        {
            cout << " mortgaged." << endl;
        }
        else
        {
            cout << " not mortgaged." << endl;
        }
        cout << "What would you like to do now?" << endl;
        // Now we return back to command to either (unmortgage/trade/sell/buy improvement)
        return;
    }
    else if (getOwner() == nullptr)
    {
        string cmd;
        cout << "This property has not been bought yet." << endl;
        cout << "Would you like to buy it for $" << getCost() << "? (Y/N) " << endl;
        cin >> cmd;
        if (cmd == "Y" || cmd == "y")
        {
            bool bought = buyProperty(p);
            if (bought)
            {
                p->addNetWorth(getCost());
                p->addBlocksOwned(blockKey);
            }
        }
        else if (cmd == "N" || cmd == "n")
        {
            cout << "Auctioning..." << endl;
        }
    }

    else if (getOwner() != p)
    {
        if (getIsMortgaged())
        {
            cout << "This property is currently being mortaged by " << getOwner()->getName() << "." << endl;
            cout << "No payment required!" << endl;
        }
        else
        {
            int tuition = 0;
            if (improvementCount == 0 && getIsMonopoly(getOwner()))
            {
                tuition = improvementTuition[0] * 2;
            }
            else
            {
                tuition = improvementTuition[improvementCount];
            }
            cout << "This property belongs to " << getOwner()->getName() << "." << endl;
            cout << "You owe " << getOwner()->getName() << " $" << tuition << ".\n"
                 << endl;
            cout << "Paying..." << endl;
            sleep_for(seconds(1));
            p->pay(tuition);
            getOwner()->collect(tuition);
            cout << "You just paid " << getOwner()->getName() << " $" << tuition << "." << endl;
            cout << "What would you like to do now?" << endl;
        }
    }
}

bool Academic::getIsMonopoly(Player *p)
{
    // if the owner owns the correct number of buildings needed in a monopoly
    if (p->getBlocksOwned(blockKey) == monopolyBlock[blockKey])
    {
        return true;
    }
    return false;
}

int Academic::getImprovementCount()
{
    return improvementCount;
}

void Academic::buyImprovement()
{
    // // If owner does not have a monopoly
    // if (getIsMonopoly(getOwner()) == false)
    // {
    //     cout << "\nYou do not own a monopoly with this building." << endl;
    //     cout << "Unable to buy improvement." << endl;
    //     return;
    // }

    // Maxed out on improvements
    // ELSE IF
    if (improvementCount == 5)
    {
        cout << "\nThis property already has the maximum of 5 improvements." << endl;
        cout << "Unable to buy improvement." << endl;
        return;
    }

    cout << "\nOne improvement for this property costs $" << improvementCost << "." << endl;
    cout << "Do you still want to improve? (Y/N)" << endl;
    string cmd;
    cin >> cmd;
    if (cmd == "Y" || cmd == "y")
    {
        getOwner()->pay(improvementCost);
        improvementCount++;
        getOwner()->addNetWorth(improvementCost);
        cout << "\nPaying..." << endl;
        sleep_for(seconds(1));
        cout << "You just bought an improvement! What do you want to do now?" << endl;
        // Add the improvement piece on board
        notifyObservers();
    }
    else // Should be a better handling....
    {
        return;
    }
}

int Academic::getImprovementCost()
{
    return improvementCost;
}

void Academic::sellImprovement()
{
    if (improvementCount == 0)
    {
        cout << "\nThis property has no improvements to sell." << endl;
        cout << "Unable to sell improvement." << endl;
        return;
    }

    cout << "\nOne improvement for this property costs $" << improvementCost << "." << endl;
    cout << "If you sell it, you will collect $" << (improvementCost / 2) << "." << endl;
    cout << "Do you still want to sell the improvement? (Y/N)" << endl;
    string cmd;
    cin >> cmd;
    if (cmd == "Y" || cmd == "y")
    {
        getOwner()->collect(improvementCost / 2);
        getOwner()->subNetWorth(improvementCost);
        cout << "\nSelling..." << endl;
        sleep_for(seconds(1));
        cout << "\nYou just sold your improvement!" << endl;
        cout << "You now have $" << getOwner()->getMoney() << "." << endl;
        improvementCount--;
        notifyObservers();
    }
    else // Should be a better handling....
    {
        return;
    }
}

void Academic::setImprovement(int amount) {
    improvementCount = amount;
}

