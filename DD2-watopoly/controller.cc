#include "controller.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
using namespace std::this_thread;
using namespace std::chrono;

using namespace std;

Controller::Controller(Game *game, ViewBoard *viewboard, bool isNewGame) : game{game}, viewboard{viewboard}, isNewGame{isNewGame}
{
}

// All the cout print statements can be made into a separate print function in display for lower coupling
void Controller::initializePlayers()
{
    map<char, string> availPieces = {
        {'G', "Goose"}, {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"}, {'P', "Professor"}, {'S', "Student"}, {'$', "Money"}, {'L', "Laptop"}, {'T', "Pink tie"}};

    int playerCount;
    cout << "Enter the amount of players playing (2-8): ";

    while (true)
    {
        try
        {
            cin >> playerCount;
            if (cin.fail() || playerCount < 2 || playerCount > 8)
            {

                cin.clear();
                cin.ignore();
                throw invalid_argument("Enter valid number of players");
            }
            break;
        }
        catch (invalid_argument &error)
        {
            cout << error.what() << endl;
        }
    }

    for (int i = 1; i <= playerCount; i++)
    {
        string playerName;
        char piece;

        cout << "\nEnter player " << i << "'s name: ";
        cin >> playerName;

        while (true)
        {
            try
            {
                cout << endl;
                viewboard->displayPieces(availPieces);
                cout << "\nChoose player " << i << "'s piece: ";
                cin >> piece;
                if (availPieces.count(piece) == 0)
                {
                    throw invalid_argument("\nEnter a valid piece please.");
                }
                break;
            }
            catch (invalid_argument &error)
            {
                cout << error.what() << endl;
            }
        }
        availPieces.erase(piece);
        game->addPlayer(playerName, piece);
    }
}

void Controller::play(bool isTest)
{

    viewboard->printWelcome();

    if (isNewGame)
    {
        initializePlayers();
    }

    for (size_t i = 0; i < game->getPlayers().size(); i++)
    {
        game->getPlayerAt(i)->notifyObservers();
    }
    viewboard->display();

    string command;
    cout << "\nThe game is now starting." << endl;
    cout << game->getCurPlayer()->getName() << "'s turn!" << endl;
    bool jailPlay = false;
    while (true)
    {
        try
        {
            // If a player is in jail, must attend before rolling dice etc...
            if (game->getCurPlayer()->getJailTurns() > 2 && jailPlay == false)
            {
                cout << "You are currently in jail." << endl;
                game->jailTurn(game->getCurPlayer());
                jailPlay = true;
            }
            cout << "Enter a command: ";
            cin >> command;

            if (command == "roll")
            {
                if (isTest)
                {
                    int pips1;
                    int pips2;
                    cin >> pips1;
                    cin >> pips2;
                    game->rollDice(pips1, pips2);
                }
                else
                {
                    game->rollDice(); // Exceptions are in roll dice
                }
            }
            else if (command == "next")
            {
                viewboard->display();
                game->nextPlayer();
                jailPlay = false;
            }
            else if (command == "mortgage")
            {
                string property;
                cin >> property;
                game->mortgage(property);
            }
            else if (command == "unmortgage")
            {
                string property;
                cin >> property;
                game->unmortgage(property);
            }
            else if (command == "assets")
            {
                viewboard->displayAssets(game->getCurPlayer());
            }
            else if (command == "save")
            {
                string filename;
                cin >> filename;
                saveGame(game, filename);
            }
            else if (command == "trade")
            {
                string name;
                string give;
                string receive;
                cin >> name >> give >> receive;
                facilitateTrade(name, give, receive);
            }
            else if (command == "improve")
            {
                string property;
                cin >> property;
                cin >> command;
                if (command == "buy")
                {
                    // Will do exception handling in game->buyImprovement();
                    game->buyImprovement(property);
                }
                else if (command == "sell")
                {
                    game->sellImprovement(property);
                }
            }
            else if (command == "print")
            {
                viewboard->display();
            }
            else if (command == "help")
            {
                viewboard->displayHelp();
            }
            else if (command == "all")
            {
                viewboard->displayAll();
            }
            else if (command == "quit") {
                break;
            }
            else
            {
                cout << "Invalid command. Type \"help\" to see list of availible commands" << endl;
            }
        }
        catch (InvalidTrade &invalidtrade)
        {
            cout << invalidtrade.displayError() << endl;
        }
        catch (NoMoney &nomoney)
        {
            if (nomoney.getBankrupt())
            {
                cout << "SORRY: You are now bankrupt" << endl;
            }
            else
            {
                cout << "You are " << nomoney.getAmount() << " dollars short, declare bankruptcy or sell your assets" << endl;
                bankruptPlayer();
            }
        }
    }
}

void Controller::bankruptPlayer()
{
    cout << game->getCurPlayer()->getName() << " IS BANKRUPT" << endl;
}

Controller::~Controller() {}

void Controller::saveGame(Game *game, string fileName)
{
    ofstream file;
    file.open(fileName);
    int playersSize = game->getPlayers().size();
    file << playersSize << endl;

    // Index of the player that called SAVE
    int index = 0;
    // Find the index in which the player is located in PLAYERS
    // If they already rolled, then set other player as first
    string name = game->getCurPlayer()->getName();
    for (int i = 0; i < playersSize; i++)
    {
        if (name == game->getPlayerAt(i)->getName())
        {
            index = i;
            if (game->getPlayerAt(i)->getRolled())
            {
                index += 1;
            }
        }
    }
    // Print all the players
    int i = 0;
    while (i < playersSize)
    {
        if (index == playersSize)
        {
            index = 0;
        }
        Player *player = game->getPlayerAt(index);
        file << player->getName() << " "
             << player->getPiece() << " "
             << player->getCupsOwned() << " "
             << player->getMoney() << " "
             << player->getIndex() << " "
             << player->getJailTurns() << endl;
        i++;
        index++;
    }
    for (int i = 0; i < 40; i++)
    {
        Square *s = game->getBoard()->getSquare1(i);
        file << s->getName() << ' ';
        Ownable *o = dynamic_cast<Ownable *>(s);
        if (o == nullptr || o->getOwner() == nullptr)
        {
            file << "BANK "
                 << "0" << endl;
            ;
        }
        else
        {
            file << o->getOwner()->getName() << " ";
            if (o->getIsMortgaged())
            {
                file << "-1" << endl;
            }
            else
            {
                Academic *a = dynamic_cast<Academic *>(o);
                file << a->getImprovementCount() << endl;
            }
        }
    }
    file.close();
}

bool Controller::checkNumber(string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
        {
            return false;
        }
    }
    return true;
}

void Controller::facilitateTrade(string name, string give, string receive)
{
    Ownable *square1 = dynamic_cast<Ownable *>(game->getBoard()->getSquare1(give));
    Ownable *square2 = dynamic_cast<Ownable *>(game->getBoard()->getSquare1(receive));
    bool matchName = false;
    for (size_t i = 0; i < game->getPlayers().size(); i++)
    {
        Player *player = game->getPlayerAt(i);
        if (player->getName() == name && player->getName() != game->getCurPlayer()->getName())
            matchName = true;
    }
    if (!matchName)
    {
        throw InvalidTrade{"is not a valid player name", name};
    }

    if (checkNumber(give) && checkNumber(receive))
    {
        throw InvalidTrade{"INVALID TRADE: Cannot trade cash for cash"};
    }

    else if (checkNumber(give) && stoi(give) > game->getCurPlayer()->getMoney())
    {
        throw InvalidTrade{"INVALID TRADE: Cannot offer more money that what you have currently"};
    }
    else if (checkNumber(receive) && stoi(receive) > game->getPlayerAt(name)->getMoney())
    {
        throw InvalidTrade{"does not have enough money for this trade", name};
    }
    else if ((!square1) && checkNumber(receive))
    {
        throw InvalidTrade{"INVALID TRADE: Property you are offering is not ownable"};
    }

    else if ((!square2) && checkNumber(give))
    {
        throw InvalidTrade{"INVALID TRADE: Property you are receiving is not ownable"};
    }

    else if ((square1) && checkNumber(receive))
    {
        if (square1->getOwner() == nullptr)
        {
            throw InvalidTrade{"is not currently owned", square1->getName()};
        }
    }
    else if ((square2) && checkNumber(give))
    {
        if (square2->getOwner() == nullptr)
        {
            throw InvalidTrade{"is not currently owned", square2->getName()};
        }
    }

    else if (!(checkNumber(receive)) && (!(checkNumber(give))))
    {
        if (square1->getOwner() == nullptr || square2->getOwner() == nullptr)
        {
            throw InvalidTrade{"is not currently owned", square1->getName()};
        }

        else if (square1->getOwner()->getName() != game->getCurPlayer()->getName())
        {
            throw InvalidTrade{"INVALID TRADE: You do not own this property"};
        }

        else if (square2->getOwner()->getName() != name)
        {

            throw InvalidTrade{"does not own this property", name};
        }
    }
    // Display valid trade
    viewboard->displayTrade(game->getCurPlayer()->getName(), name, give, receive);

    string decision;
    cout << name << ": do you accept this trade?(accept/reject)" << endl;
    cin >> decision;
    if (decision == "accept")
    {
        if (checkNumber(give))
        {
            int giveAmount = stoi(give);
            game->executeTrade(game->getPlayerAt(name), giveAmount, receive);
        }
        else if (checkNumber(receive))
        {
            int receiveAmount = stoi(receive);
            game->executeTrade(game->getPlayerAt(name), give, receiveAmount);
        }
        else
        {
            game->executeTrade(game->getPlayerAt(name), give, receive);
        }
    }
}

void Controller::loadGame(Game *game, ViewBoard *viewboard, std::string file)
{
    ifstream myfile{file};
    string input;

    // get number of players
    int numPlayers;
    getline(myfile, input);
    istringstream ss{input};
    ss >> numPlayers;

    string name;
    char piece;
    int cupsOwned;
    int money;
    int index;
    int jailTurns;

    // load in players
    for (int i = 0; i < numPlayers; i++)
    {
        getline(myfile, input);
        istringstream playerInfo{input};

        playerInfo >> name;
        playerInfo >> piece;
        playerInfo >> cupsOwned;
        playerInfo >> money;
        playerInfo >> index;
        playerInfo >> jailTurns;

        game->addPlayer(name, piece);

        game->getPlayerAt(i)->setCupsOwned(cupsOwned);
        game->getPlayerAt(i)->setMoney(money);
        game->getPlayerAt(i)->move(index);
        game->getPlayerAt(i)->setJailTurns(jailTurns);
    }

    // load in properties
    string squareName;
    string squareOwner;
    int squareImprovements;
    string unused;
    vector<int> hardPos{0, 7, 10, 20, 22, 30, 36, 38};
    for (int i = 0; i < 40; i++)
    {

        getline(myfile, input);
        istringstream squareInfo{input};
        if (find(hardPos.begin(), hardPos.end(), i) != hardPos.end())
        {
            squareName = game->getBoard()->getSquare1(i)->getName();
            if (i == 10 || i == 30)
            {
                squareInfo >> unused;
                squareInfo >> unused;
                squareInfo >> unused;
            }
            else
            {
                squareInfo >> unused;
                squareInfo >> unused;
            }
        }
        else
        {
            squareInfo >> squareName;
        }
        squareInfo >> squareOwner;
        squareInfo >> squareImprovements;

        if (squareOwner != "BANK")
        {
            // Set owner
            Square *s = game->getBoard()->getSquare1(squareName);
            Ownable *o = dynamic_cast<Ownable *>(s);
            Player *p = game->getPlayerAt(squareOwner);
            o->setOwner(p);

            // Set improvement count and monopoly for academics
            Academic *a = dynamic_cast<Academic *>(s);
            if (a)
            {
                cout << "12" << endl;
                a->setImprovement(squareImprovements);

                // cout << "13" << endl;
                // string x = a->getBlockKey();
                // p->addBlocksOwned(x);
                // cout << "14" << endl;
            }
        }
    }
}

