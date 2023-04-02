#include "slc.h"

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

SLC::SLC(std::string name, int index) : Square{name, index} {}

int SLC::getMove()
{
    std::vector<int> moves = {-3, -3, -3, 3, 3, 3, 3, -2, -2, -2, -2, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 5};
    // Tims cup 1%
    srand(time(NULL));
    int cup = rand() % 100 + 1;
    if (cup == 1)
    {
        return 6;
    }
    // Moves
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
    return moves[0];
}

void SLC::action(Player *p)
{
    const int TIMS = 10;
    const int OSAP = 0;
    int move = getMove();
    cout << "You landed on SLC! Generating action...\n"
         << endl;
    sleep_for(seconds(1));
    if (move == 6 && p->getActiveCups() < 4)
    {
        cout << "OMG! You earned a tims cup! This will come in handy for later." << endl;
        p->addRimCup();
        p->addActiveCups();
        cout << "What would you like to do now?" << endl;
        return;
    }
    else if (move == 6 && p->getActiveCups() >= 4)
    {
        cout << "OMG! You were supposed to get a tims cup, but they were all taken!" << endl;
        cout << "What would you like to do now?" << endl;
        return;
    }
    else if (move == 4)
    {
        cout << "Oh no! You are moving to the Tims Line!" << endl;
        cout << "Moving...\n"
             << endl;
        sleep_for(seconds(1));
        p->setJailTurns(1);
        p->moveAndLand(TIMS); // Tims Line
    }
    else if (move == 5)
    {
        cout << "You are moving to Collect OSAP!" << endl;
        cout << "Moving...\n"
             << endl;
        sleep_for(seconds(1));
        p->moveAndLand(OSAP); // Collect OSAP
    }
    else if (move < 0)
    {
        cout << "Oh no! You are moving back " << (-1 * move) << " spaces." << endl;
        cout << "Moving...\n"
             << endl;
        sleep_for(seconds(1));

        // If SLC at index 2, whereTo might be 39 (move back 3)
        if (p->getIndex() == 2 && move == -3)
        {
            p->moveAndLand(39);
        }
        else
        {
            int whereTo = p->getIndex() + move;
            p->moveAndLand(whereTo);
        }
    }
    else if (move > 0)
    {
        cout << "Lucky you! You are moving forward " << move << " spaces." << endl;
        cout << "Moving...\n"
             << endl;
        sleep_for(seconds(1));
        int whereTo = p->getIndex() + move;
        p->moveAndLand(whereTo);
    }
}

