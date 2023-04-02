#ifndef NOMONEY_H
#define NOMONEY_H


class NoMoney
{
    int amount;
    bool bankrupt;

public:
    NoMoney(int amount) : amount{amount} {}
    NoMoney(bool bankrupt) : bankrupt{bankrupt} {}
    int getAmount() {
        return amount;
    }
    int getBankrupt() {
        return bankrupt;
    }
};

#endif

