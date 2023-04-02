#ifndef TIMSLINE_H
#define TIMSLINE_H
#include "square.h"
#include "player.h"
#include "game.h"

class Game;

class TimsLine : public Square
{
    Game *game;
    
public:
    TimsLine(std::string name, int index, Game *game);
    void action(Player *p) override;
};

#endif
