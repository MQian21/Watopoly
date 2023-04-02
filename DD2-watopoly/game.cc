#include <iostream>
#include <sstream>
#include "game.h"

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

Game::Game() : Subject{}, board{make_unique<Board>(this)}, dice{make_unique<Dice>(6, 6)}, curPlayerIndex{0}
{
}

Game::~Game() {}

vector<Player *> Game::getPlayers()
{
    return players;
}

void Game::addPlayer(string playerName, char token)
{
    Player *p = new Player{
        this,
        playerName,
        token};
    players.emplace_back(p);
    if (players.size() == 1)
    {
        curPlayer = players[0];
    }
    attachObservers(p);
}

void Game::nextPlayer()
{
    curPlayer->setRolled(false);
    if (curPlayer->getJailTurns() == 2)
    {
        curPlayer->setJailTurns(3);
    }
    curPlayerIndex++;
    int playersLen = static_cast<int>(players.size());
    if (curPlayerIndex == playersLen)
    {
        curPlayerIndex = 0;
    }
    curPlayer = players[curPlayerIndex];
    cout << endl;
    cout << curPlayer->getName() << "'s turn!" << endl;
}

void Game::rollDice(int pips1, int pips2)
{
    const int TIMS = 10;
    Dice d = Dice{pips1, pips2};

    // If the player is stuck in jail, cannot roll
    if (curPlayer->getJailTurns() >= 1)
    {
        cout << "\nYou cannot roll the dice. You're stuck in line!" << endl;
        return;
    }

    if (curPlayer->getRolled())
    {
        cout << "\nYou already rolled!" << endl;
        return;
    }

    int doubleCount = 0;
    curPlayer->setRolled(true);
    for (int i = 1; i <= 3; i++)
    {
        if (curPlayer->getJailTurns() >= 1)
        {
            return;
        }
        int rolled = d.roll();
        bool isDouble = d.getIsDouble();
        cout << "Total: " << rolled;

        if (isDouble && i == 3)
        {
            cout << "\nOMG! A double on your third roll!! You're going to the Tims Line. " << endl;
            cout << "\n\nMoving..." << endl;
            sleep_for(seconds(1));
            curPlayer->setJailTurns(1);
            curPlayer->moveAndLand(TIMS);
            return;
        }
        if (isDouble)
        {
            doubleCount++;
            cout << "\nA double! Now you must roll again after your play on the square." << endl;
        }
        cout << "\n\nMoving..." << endl;
        sleep_for(seconds(1));
        // move(rolled) returns where the player landed on the board
        int playerLandIndex = curPlayer->move(rolled);
        // Take action on the square located on gameBoard[playerLandIndex]
        board->getSquare(playerLandIndex).action(curPlayer);
        // If it wasn't a double, cannot roll again
        if (!isDouble)
        {
            // If not a double, do not roll again
            return;
        }
    }
}

void Game::rollDice()
{
    const int TIMS = 10;

    // If the player is stuck in jail, cannot roll
    if (curPlayer->getJailTurns() >= 1)
    {
        cout << "\nYou cannot roll the dice. You're stuck in line!" << endl;
        return;
    }

    if (curPlayer->getRolled())
    {
        cout << "\nYou already rolled!" << endl;
        return;
    }

    int doubleCount = 0;
    curPlayer->setRolled(true);
    for (int i = 1; i <= 3; i++)
    {
        if (curPlayer->getJailTurns() >= 1)
        {
            return;
        }
        int rolled = dice->roll();
        bool isDouble = dice->getIsDouble();
        cout << "Total: " << rolled;

        if (isDouble && i == 3)
        {
            cout << "\nOMG! A double on your third roll!! You're going to the Tims Line. " << endl;
            cout << "\n\nMoving..." << endl;
            sleep_for(seconds(1));
            curPlayer->setJailTurns(1);
            curPlayer->moveAndLand(TIMS);
            return;
        }
        if (isDouble)
        {
            doubleCount++;
            cout << "\nA double! Now you must roll again after your play on the square." << endl;
        }
        cout << "\n\nMoving..." << endl;
        sleep_for(seconds(1));
        // move(rolled) returns where the player landed on the board
        int playerLandIndex = curPlayer->move(rolled);
        // Take action on the square located on gameBoard[playerLandIndex]
        board->getSquare(playerLandIndex).action(curPlayer);
        
        // If it wasn't a double, cannot roll again
        if (!isDouble)
        {
            // If not a double, do not roll again
            return;
        }
    }
}

void Game::jailTurn(Player *p)
{
    const int TIMSLINE = 10;
    board->getSquare(TIMSLINE).action(curPlayer);
}

void Game::attachPlayers(Observer *o)
{
    for (auto p = players.begin(); p != players.end(); p++)
    {
        (*p)->attachV2(o);
    }
}

void Game::attachSquares(Observer *o)
{
    for (int i = 0; i < 40; i++)
    {
        Square &s = board->getSquare(i);
        (&s)->attachV2(o);
    }
}

Player *Game::getCurPlayer()
{
    return curPlayer;
}

void Game::buyImprovement(string property)
{
    Academic *a = dynamic_cast<Academic *>(board->getSquare1(property));
    // Was unable to cast to Academic
    if (!a)
    {
        cout << "\nThis is not an academic building, you cannot improve it." << endl;
        return;
    }

    // Building does not belong to curPlayer who is trying to improve
    else if (a->getOwner() == nullptr)
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }

    else if (a->getOwner()->getName() != curPlayer->getName())
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }

    // Works
    a->buyImprovement();
}

void Game::sellImprovement(std::string property)
{
    Academic *a = dynamic_cast<Academic *>(board->getSquare1(property));

    // Was unable to cast to Academic
    if (!a)
    {
        cout << "\nThis is not an academic building, it has no improvements." << endl;
        return;
    }

    else if (a->getOwner() == nullptr)
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }

    // Building does not belong to curPlayer who is trying to improve
    else if (a->getOwner()->getName() != curPlayer->getName())
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }
    // Works
    a->sellImprovement();
}

Board *Game::getBoard()
{
    return board.get();
}

Player *Game::getPlayerAt(int i)
{
    return players[i];
}

Player *Game::getPlayerAt(string name)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        if (players[i]->getName() == name)
        {
            return players[i];
        }
    }
    return nullptr;
}

void Game::mortgage(string property)
{
    Ownable *o = dynamic_cast<Ownable *>(board->getSquare1(property));
    if (!o)
    {
        cout << "\nThis is not an ownable building." << endl;
        return;
    }
    if (o->getOwner() == nullptr)
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }
    else if (o->getOwner()->getName() != curPlayer->getName())
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }
    // Check if it is already mortgaged
    else if (o->getIsMortgaged())
    {
        cout << "\nThis property is already mortgaged." << endl;
        return;
    }
    Academic *a = dynamic_cast<Academic *>(board->getSquare1(property));
    // It's an academic building, check for improvement count
    if (a)
    {
        if (a->getImprovementCount() > 0)
        {
            cout << "This property has improvements, you can't mortgage." << endl;
            return;
        }
    }
    int cost = o->getCost();
    o->setMortgaged(true);
    o->getOwner()->collect(cost / 2);
    cout << "\nMortgaging... Collecting..." << endl;
    sleep_for(seconds(1));
    cout << "You just mortgaged the property!" << endl;
    cout << "You now have $" << o->getOwner()->getMoney() << "." << endl;
    cout << "\nWhat would you like to do now?" << endl;
    return;
}

void Game::unmortgage(string property)
{
    Ownable *o = dynamic_cast<Ownable *>(board->getSquare1(property));
    if (!o)
    {
        cout << "This is not an ownable building." << endl;
        return;
    }
    else if (o->getOwner() == nullptr)
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }
    else if (o->getOwner()->getName() != curPlayer->getName())
    {
        cout << "\nThis building does not belong to you." << endl;
        return;
    }
    else if (!o->getIsMortgaged())
    {
        cout << "\nThis building is already unmortgaged." << endl;
        return;
    }
    int cost = (0.6 * o->getCost());
    o->setMortgaged(false);
    o->getOwner()->pay(cost);
    cout << "\nUnmortgaging... Paying..." << endl;
    sleep_for(seconds(1));
    cout << "You just unmortgaged the property!" << endl;
    cout << "You now have $" << o->getOwner()->getMoney() << "." << endl;
    cout << "\nWhat would you like to do now?" << endl;
    return;
}

void Game::executeTrade(Player *name, std::string give, std::string receive)
{
    Ownable *sendSquare = dynamic_cast<Ownable *>(board->getSquare1(give));
    Ownable *receiveSquare = dynamic_cast<Ownable *>(board->getSquare1(receive));
    sendSquare->setOwner(name);
    receiveSquare->setOwner(curPlayer);
}
void Game::executeTrade(Player *name, int giveAmount, std::string receive)
{
    Ownable *receiveSquare = dynamic_cast<Ownable *>(board->getSquare1(receive));
    receiveSquare->setOwner(curPlayer);
    curPlayer->pay(giveAmount);
    name->collect(giveAmount);
}
void Game::executeTrade(Player *name, std::string give, int receiveAmount)
{
    Ownable *sendSquare = dynamic_cast<Ownable *>(board->getSquare1(give));
    sendSquare->setOwner(name);
    name->pay(receiveAmount);
    curPlayer->collect(receiveAmount);
}

Dice *Game::getDice()
{
    return dice.get();
}

