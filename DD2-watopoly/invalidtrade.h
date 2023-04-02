#ifndef INVALIDTRADE_H
#define INVALIDTRADE_H
#include <string>

class InvalidTrade
{
    std::string message;
    std::string name;

public:
    InvalidTrade(std::string message, std::string name);
    InvalidTrade(std::string message);
    std::string displayError();
};

#endif

