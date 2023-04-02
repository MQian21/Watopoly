#include "timsline.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

TimsLine::TimsLine(std::string name, int index, Game *game) : Square{name, index}, game{game} {}

void TimsLine::action(Player *p)
{
    if (p->getJailTurns() == 0)
    {
        cout << "You landed on " << getName() << "!\n"
             << endl;

        sleep_for(seconds(1));
        cout << "Mmm. Grabbed a hot coffee." << endl;
        cout << "What would you like to do now?" << endl;
        return;
    }
    else if (p->getJailTurns() == 1)
    {
        cout << "You are now on " << getName() << "!" << endl;
        sleep_for(seconds(1));
        cout << "You're stuck! What would you like to do now?" << endl;
        p->setJailTurns(2);
        return;
    }
    else if (p->getJailTurns() >= 2)
    {
        cout << "You have the option of escaping by either:" << endl;
        cout << "1. Rolling doubles\n2. Paying $50\n3. Using a Tims cup\n"
             << endl;
        cout << "What would you like to do? (1/2/3)" << endl;
        string cmd;
        cin >> cmd;

        // Choose Dice
        if (cmd == "1")
        {
            Dice *d = game->getDice();
            int rolled = d->roll();
            bool isDouble = d->getIsDouble();
            // Gets a double
            if (isDouble)
            {
                p->setJailTurns(0);
                cout << "\nOMG! You rolled a double! You were able to escape the line..." << endl;
                sleep_for(seconds(1));
                cout << "You moved, but cannot take another turn. What would you like to do now?\n"
                     << endl;
                     
                p->setRolled(true);
                int whereTo = p->getIndex() + rolled;
                p->move(whereTo);
                p->setJailTurns(0);
                return;
            }
            // Not a double
            else
            {
                // First time rolling
                if (p->getJailTurns() == 2)
                {
                    cout << "\nNot a double! Looks like you're stuck here again" << endl;
                    cout << "What do you want to do now?" << endl;
                    p->setJailTurns(3);
                    return;
                }
                // Second time rolling
                else if (p->getJailTurns() == 3)
                {
                    cout << "\nNot a double! Looks like you're stuck here again" << endl;
                    cout << "What do you want to do now?" << endl;
                    p->setJailTurns(4);
                    return;
                }
                // Third (final) time rolling
                else if (p->getJailTurns() == 4)
                {
                    cout << "\nNot a double! Now you have to pay $50 or use a Tims cup" << endl;
                    cout << "What do you choose? ($50/Cup)" << endl;
                    cin >> cmd;
                    if (cmd == "$50")
                    {
                        cout << "You just paid $50 and are now out of jail!" << endl;
                        p->pay(50);
                        p->setJailTurns(0);
                    }
                    if (cmd == "Cup")
                    {
                        cout << "You just used a Tims Cup and are now out of jail!" << endl;
                        p->subRimCup();
                        p->subActiveCups();
                        p->setJailTurns(0);
                    }
                    cout << "\n"
                         << endl;
                    cout << "You moved, but cannot take another turn.\nWhat would you like to do now?" << endl;
                    int whereTo = p->getIndex() + rolled;
                    p->move(whereTo);
                }
            }
        }
        // Pay $50 (BEFORE ROLLING THE DICE)
        else if (cmd == "2")
        {

            // CHECK FOR ERROR!!!
            cout << "You just paid $50 and are now out of jail!" << endl;
            cout << "What would you like to do now?" << endl;
            p->pay(50);
            p->setJailTurns(0);
        }
        // Use Tims Cup (BEFORE ROLLING THE DICE)
        else if (cmd == "3")
        {

            // CHECK FOR ERROR HANDLIN!!!
            cout << "You just used a Tims Cup and are now out of jail!" << endl;
            cout << "What would you like to do now?" << endl;
            p->subRimCup();
            p->subActiveCups();
        }
    }
}
