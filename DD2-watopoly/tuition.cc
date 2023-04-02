#include "tuition.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

Tuition::Tuition(std::string name, int index) : Square{name, index} {}

void Tuition::action(Player *p)
{
    cout << "You landed on Tuition!" << endl;
    sleep_for(seconds(1));
    cout << "Would you like to pay $300 tuition or 10% of you total net worth? ($300/10%)" << endl;
    string cmd;
    cin >> cmd;
    if (cmd == "$300")
    {
        cout << "\nYou just paid $300." << endl;
        p->pay(300);
    }
    else if (cmd == "10%")
    {
        cout << "\nYou just paid $" << (p->getNetWorth() * 0.1) << "." << endl;
        int amount = (p->getNetWorth() * 0.1);
        p->pay(amount);
    }
    cout << "You now have $" << p->getMoney() << "." << endl;
    cout << "What would you like to do now?" << endl;
}

