#include "coopfee.h"

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono; 

using namespace std;

CoopFee::CoopFee(std::string name, int index) : Square{name, index} {}

void CoopFee::action(Player *p) {
    cout << "You landed on Coop Fee! You owe the school $150." << endl;
    sleep_for(seconds(1));
    cout << "\nPaying..." << endl;
    sleep_for(seconds(1));
    p->pay(150);
    cout << "You just paid $150 to the bank. What would you like to do now?" << endl;
}

