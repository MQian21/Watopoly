#include "goosenesting.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;


GooseNesting::GooseNesting(std::string name, int index) : Square{name, index} {}


void GooseNesting::action(Player *p) {
    cout << "You landed on Goose Nesting...\n" << endl;
    sleep_for(seconds(1));
    cout << "Ouch! You were attacked by a flock of geese!" << endl;
    cout << "What would you like to do now?" << endl;
}

