#ifndef GAME_H
#define GAME_H
#include "subject.h"
#include "viewboard.h"
#include "player.h"
#include "dice.h"
#include "board.h"
#include <memory>
#include <string>

class Player;
class Subject;
class Dice;
class Board;

class Game : public Subject
{
    std::vector<Player *> players;
    std::unique_ptr<Board> board;
    std::unique_ptr<Dice> dice;
    Player *curPlayer;
    int curPlayerIndex;

public:
    Game();
    virtual ~Game();
    void rollDice();
    void rollDice(int die1, int die2);
    void jailTurn(Player *p);
    void nextPlayer();
    void addPlayer(std::string playerName, char token);
    void attachSquares(Observer *o) override;
    void attachPlayers(Observer *o) override;
    Player *getCurPlayer();
    void buyImprovement(std::string property);
    void sellImprovement(std::string property);
    std::vector<Player *> getPlayers();
    void displayAssets(Player *p);
    Board *getBoard();
    Player *getPlayerAt(int i);
    Player *getPlayerAt(std::string name);
    void executeTrade(Player *name, std::string give, std::string receive);
    void executeTrade(Player *name, int giveAmount, std::string receive);
    void executeTrade(Player *name, std::string give, int receiveAmount);
    void mortgage(std::string property);
    void unmortgage(std::string property);
    Dice * getDice();
    void auction(Player *p);
};

#endif

