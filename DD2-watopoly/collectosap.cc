#include "collectosap.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std::this_thread;
using namespace std::chrono; 

using namespace std;

CollectOSAP::CollectOSAP(std::string name, int index) : Square{name, index} {}

void CollectOSAP::action(Player *p) {
    cout << "You landed on Collect OSAP!" << endl;
    p->collect(200);
    sleep_for(milliseconds(700));
    cout << "You just collected $200. What would you like to do now?" << endl;
}

