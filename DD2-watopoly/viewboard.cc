#include "viewboard.h"
#include <iterator>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

const string baseBoard{
    "____________________________________________________________________________________________________\n"
    "|GOOSE   |        |NEEDLES |        |        |V1      |        |        |CIF     |        |GO TO   |\n"
    "|NESTING |--------|HALL    |--------|--------|        |--------|--------|        |--------|TIMS    |\n"
    "|        |EV1     |        |EV2     |EV3     |        |PHYS    |B1      |        |B2      |        |\n"
    "|        |        |        |        |        |        |        |        |        |        |        |\n"
    "|________|________|________|________|________|________|________|________|________|________|________|\n"
    "|        |                                                                                |        |\n"
    "|--------|                                                                                |--------|\n"
    "|OPT     |                                                                                |EIT     |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|        |                                                                                |        |\n"
    "|--------|                                                                                |--------|\n"
    "|BMH     |                                                                                |ESC     |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|SLC     |                                                                                |SLC     |\n"
    "|        |                                                                                |        |\n"
    "|        |                                                                                |        |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|        |                                                                                |        |\n"
    "|--------|                                                                                |--------|\n"
    "|LHI     |                                                                                |C2      |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|UWP     |                   #   # #### ##### ##### #### ##### #    #   #                 |REV     |\n"
    "|        |                   #   # #  #   #   #   # #  # #   # #    #   #                 |        |\n"
    "|        |                   # # # ####   #   #   # #### #   # #     ###                  |        |\n"
    "|        |                   # # # #  #   #   #   # #    #   # #      #                   |        |\n"
    "|________|                   ##### #  #   #   ##### #    ##### ####   #                   |________|\n"
    "|        |                                                                                |NEEDLES |\n"
    "|--------|                                                                                |HALL    |\n"
    "|CPH     |                                                                                |        |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|        |                                                                                |        |\n"
    "|--------|                                                                                |--------|\n"
    "|DWE     |                                                                                |MC      |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|PAC     |                                                                                |COOP    |\n"
    "|        |                                                                                |FEE     |\n"
    "|        |                                                                                |        |\n"
    "|        |                                                                                |        |\n"
    "|________|                                                                                |________|\n"
    "|        |                                                                                |        |\n"
    "|--------|                                                                                |--------|\n"
    "|RCH     |                                                                                |DC      |\n"
    "|        |                                                                                |        |\n"
    "|________|________________________________________________________________________________|________|\n"
    "|DC TIMS |        |        |NEEDLES |        |MKV     |TUITION |        |SLC     |        |COLLECT |\n"
    "|LINE    |--------|--------|HALL    |--------|        |        |--------|        |--------|OSAP    |\n"
    "|        |HH      |PAS     |        |ECH     |        |        |ML      |        |AL      |        |\n"
    "|        |        |        |        |        |        |        |        |        |        |        |\n"
    "|________|________|________|________|________|________|________|________|________|________|________|\n"};

ViewBoard::ViewBoard(Game *game) : game{game}, boardDisplay{baseBoard}, updateCount{0}
{
    // Initialize the playerPrevious by adding key-value pairs
    for (size_t i = 0; i < game->getPlayers().size(); i++)
    {
        string name = game->getPlayerAt(i)->getName();
        playerPrevious[name] = 0;
    }

    // Placing where each player/improvement needs to go on a square

    // Bottom
    int playerLoc = 5544; // COLLECT OSAP
    int improveLoc = 5243;
    for (int i = 0; i < 10; i++)
    {
        playerPlace.emplace_back(playerLoc);
        improvePlace.emplace_back(improveLoc);
        playerLoc -= 9;
        improveLoc -= 9;
        // 7 forward away
    }
    // Left
    playerLoc = 5454; // DC TIMS LINE
    improveLoc = 5153;
    for (int i = 0; i < 10; i++)
    {
        playerPlace.emplace_back(playerLoc);
        improvePlace.emplace_back(improveLoc);
        playerLoc -= 505;
        improveLoc -= 505;
    }
    // Top
    playerLoc = 405; // GOOSE NESTING
    improveLoc = 103;
    for (int i = 0; i < 10; i++)
    {
        playerPlace.emplace_back(playerLoc);
        improvePlace.emplace_back(improveLoc);
        playerLoc += 9;
        improveLoc += 9;
    }
    // Right
    playerLoc = 495; // GO TO TIMS
    improveLoc = 193;
    for (int i = 0; i < 10; i++)
    {
        playerPlace.emplace_back(playerLoc);
        improvePlace.emplace_back(improveLoc);
        playerLoc += 505;
        improveLoc += 505;
    }
    game->attach(this);
}

void ViewBoard::notify(Subject *whoNotified)
{
    Player *p = dynamic_cast<Player *>(whoNotified);
    if (p)
    {
        if (updateCount == 0)
        {
            // If it is the first update of a player, no need to previous
            updateCount++;
        }
        else
        {
            // Take out where the player was previously
            int previous = playerPrevious[p->getName()];
            boardDisplay[previous] = ' ';
        }
        // Change location
        int boardLocation = playerPlace[p->getIndex()];
        while (boardDisplay[boardLocation] != ' ')
        { // While another player is not there
            boardLocation++;
        }
        boardDisplay[boardLocation] = p->getPiece();
        playerPrevious[p->getName()] = boardLocation;
        return;
    }

    Academic *a = dynamic_cast<Academic *>(whoNotified);
    if (a)
    {
        int boardLocation = improvePlace[a->getIndex()];
        // Remove all improvements
        for (int i = 0; i < 5; i++)
        {
            boardDisplay[boardLocation] = ' ';
            boardLocation++;
        }

        boardLocation = improvePlace[a->getIndex()];
        // Print correct ammount of improvements
        int improveCount = a->getImprovementCount();
        for (int i = 0; i < improveCount; i++)
        {
            boardDisplay[boardLocation] = '^';
            boardLocation++;
        }
        return;
    }
}

void ViewBoard::display()
{
    cout << boardDisplay;
}

void ViewBoard::printWelcome()
{
    // cout << "\nWᴇʟᴄᴏᴍᴇ ᴛᴏ Wᴀᴛᴏᴘᴏʟʏ!\n"
    cout << "Welcome" << endl;
}

void ViewBoard::displayPieces(map<char, string> availPieces)
{
    cout << "----Availible Pieces----" << endl;
    for (auto &p : availPieces)
    {
        cout << p.first << ' ' << p.second << endl;
    }
}

void ViewBoard::displayTrade(string trader, string target, string give, string receive)
{
    cout << "---TRADE PROPOSAL---" << endl;
    cout << "____________________" << endl;
    cout << setw(7) << trader << ": " << give << endl;
    cout << setw(7) << target << ": " << receive << endl;
    cout << "\n"
         << endl;
}

void ViewBoard::displayHelp()
{
    cout << "\n------------Commands-----------" << endl;
    cout << "roll" << endl;
    cout << "next" << endl;
    cout << "print" << endl;
    cout << "trade <name> <give> <receive>" << endl;
    cout << "improve <property> <buy>/<sell>" << endl;
    cout << "mortgage <property>" << endl;
    cout << "unmortgage <property>" << endl;
    cout << "bankrupt" << endl;
    cout << "assets" << endl;
    cout << "all" << endl;
    cout << "save <filename>\n"
         << endl;
}

void ViewBoard::displayAssets(Player *p)
{
    cout << "\n----" << p->getName() << "'s Assets----"
         << endl;
    cout << "Money: $" << p->getMoney() << endl;
    cout << "Properties:" << endl;
    for (int i = 0; i < 40; i++)
    {
        Ownable *o = dynamic_cast<Ownable *>(game->getBoard()->getSquare1(i));
        if (o != nullptr)
        {
            if (o->getOwner() != nullptr)
            {
                if (o->getOwner()->getName() == p->getName())
                {
                    cout << o->getName() << endl;
                }
            }
        }
    }
    cout << "Tims Cups: " << p->getCupsOwned() << endl;
    cout << "Net Worth: $" << p->getNetWorth() << endl;
    cout << endl;
}

void ViewBoard::displayAll()
{
    int len = game->getPlayers().size();
    for (int i = 0; i < len; i++)
    {
        Player *p = game->getPlayerAt(i);
        cout << "\n----" << p->getName() << "'s Assets----"
             << endl;
        cout << "Money: $" << p->getMoney() << endl;
        cout << "Properties:" << endl;
        for (int i = 0; i < 40; i++)
        {
            Ownable *o = dynamic_cast<Ownable *>(game->getBoard()->getSquare1(i));
            if (o != nullptr)
            {
                if (o->getOwner() != nullptr)
                {
                    if (o->getOwner()->getName() == p->getName())
                    {
                        cout << o->getName() << endl;
                    }
                }
            }
        }
        cout << "Tims Cups: " << p->getCupsOwned() << endl;
        cout << "Net Worth: $" << p->getNetWorth() << endl;
        cout << endl;
    }
}

