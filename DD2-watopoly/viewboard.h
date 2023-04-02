#ifndef VIEWBOARD_H
#define VIEWBOARD_H
#include "observer.h"
#include "subject.h"
#include "game.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Game;
class Player;
class Academic;
class Subject;

class ViewBoard : public Observer
{
    Game *game;
    std::string boardDisplay;
    int updateCount;
    std::vector<int> playerPlace;
    std::vector<int> improvePlace;
    std::map<std::string, int> playerPrevious;

public:
    ViewBoard(Game *game);
    void notify(Subject *whoNotified) override;
    void display();
    void printWelcome();
    void displayPieces(std::map<char, std::string> availPieces);
    void displayHelp();
    void displayAssets(Player *p);
    void displayTrade(std::string trader, std::string target, std::string give, std::string receive);
    void displayAll();
};

#endif

