#include "gotims.h"
#include "player.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

GoTims::GoTims(std::string name, int index) : Square{name, index} {}

void GoTims::action(Player *p) {
    const int TIMSLINE = 10;
    cout << "Oh no! You landed on Go to Tims!\n" << endl;
    cout << "You are now forced to move to the DC Tims line.\n" << endl;
    cout << "Moving..." << endl;
    p->setJailTurns(1);
    sleep_for(seconds(1));
    p->moveAndLand(TIMSLINE);
}

