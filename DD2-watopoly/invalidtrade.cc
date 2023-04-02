#include "invalidtrade.h"
#include <sstream>
#include <iostream>

using namespace std;

InvalidTrade::InvalidTrade(string message) : message{message} {}

InvalidTrade::InvalidTrade(string message, string name) : message{message}, name{name} {}

string InvalidTrade::displayError()
{
    return (name + message);
}

