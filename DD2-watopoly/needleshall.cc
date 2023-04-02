#include "needleshall.h"
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

NeedlesHall::NeedlesHall(std::string name, int index) : Square{name, index} {}

int NeedlesHall::getChange()
{
    std::vector<int> changes = {-200, -100, -100, -50, -50, -50, 25, 25, 25, 25, 25, 25, 50, 50, 50, 100, 100, 200};
    // cup
    srand(time(NULL));
    int cup = rand() % 100 + 1;
    if (cup == 1)
    {
        return 1;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(changes.begin(), changes.end(), std::default_random_engine(seed));
    return changes[0];
}

void NeedlesHall::action(Player *p)
{
    int change = getChange();
    cout << "You landed on Needles Hall! Generating action...\n"
         << endl;
    sleep_for(seconds(1));
    if (change == 1 && p->getActiveCups() < 4)
    {
        cout << "OMG! You earned a tims cup! This will come in handy for later." << endl;
        p->addRimCup();
        p->addActiveCups();
        cout << "What would you like to do now?" << endl;
        return;
    }
    else if (change == 1 && p->getActiveCups() >= 4)
    {
        cout << "OMG! You were supposed to get a tims cup, but they were all taken!" << endl;
        cout << "What would you like to do now?" << endl;
        return;
    }
    else if (change < 0)
    {
        cout << "Oh no! You just lost $" << (-1 * change) << "." << endl;
        p->pay(-1*change);
    }
    else
    {
        cout << "Lucky you! You just earned $" << change << "." << endl;
        p->collect(change);
    }
    cout << "You now have $" << p->getMoney() << "." << endl;
}

