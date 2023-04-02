#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "viewboard.h"
#include "invalidtrade.h"
#include "game.h"

// Forward declaration of class Game/Dice so that we can use game/dice pointers
class Game;
class Dice;
class ViewBoard;
class InvalidTrade;
// class Commands;

class Controller
{
    Game *game;
    ViewBoard *viewboard;
    bool isNewGame;

    void initializePlayers();
    // We need to display board after almost every command
    // Thus - call this function and invoke displayBoard class
    void displayBoard();
    void facilitateTrade(std::string name, std::string give, std::string receive);
    void saveGame(Game *game, std::string fileName);
    bool checkNumber(std::string str);
    void bankruptPlayer();

public:
    Controller(Game *game, ViewBoard *viewboard, bool isNewGame);
    // Main needs to call play that's why it's public
    void play(bool isTest);
    void loadGame(Game *game, ViewBoard *viewboard, std::string fileName);
    virtual ~Controller();
};

#endif

