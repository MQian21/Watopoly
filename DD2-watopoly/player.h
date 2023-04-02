#ifndef PLAYER_H
#define PLAYER_H
#include "game.h"
#include <vector>
#include <map>
#include "dice.h"
#include "nomoney.h"

class Game;

class Player : public Subject
{
    // Keep track of all active cups in game
    static int activeCups;

    Game *game;
    int index;
    // Square * curSquare;
    std::string name;
    char piece;
    int money;
    int netWorth;
    int residenceOwned;
    int gymsOwned;
    int cupsOwned;
    int jailTurns;
    bool rolled;
    bool calledAuction;
    std::map<std::string, int> blocksOwned;

public:
    Player(Game *game, std::string name, char piece);
    std::string getName();
    char getPiece();
    int getIndex();
    int getMoney();
    int getNetWorth();
    void addNetWorth(int amount);
    void subNetWorth(int amount);
    int move(int spaces);
    void moveAndLand(int index);
    void pay(int amount);
    void collect(int amount);
    void addBlocksOwned(std::string blockname);
    void subBlocksOwned(std::string blockname);
    int getBlocksOwned(std::string blockname);
    int getResidenceOwned();
    void addResidenceOwned();
    void subResidenceOwned();
    int getGymsOwned();
    void addGymsOwned();
    void subGymsOwned();
    int getCupsOwned();
    void addRimCup();
    void subRimCup();
    int getActiveCups();
    void subActiveCups();
    void addActiveCups();
    void setJailTurns(int turns);
    int getJailTurns();
    bool getRolled();
    void setRolled(bool state);
    bool getCalledAuction();
    void setCalledAuction(bool state);
    void setCupsOwned(int amount);
    void setMoney(int amount);
};

#endif

