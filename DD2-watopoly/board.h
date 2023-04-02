#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include <memory>

#include "square.h"
#include "game.h"

#include "ownable.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"

#include "collectosap.h"
#include "timsline.h"
#include "gotims.h"
#include "goosenesting.h"
#include "tuition.h"
#include "coopfee.h"
#include "slc.h"
#include "needleshall.h"

class Square;
class Game;

class Board
{
    Game *game;
    std::vector<std::shared_ptr<Square>> gameBoard; // make the board of all 40 squares
    
public:
    Board(Game *g);                             // constructor
    Square &getSquare(std::string name); // get square by property name
    Square &getSquare(int index);        // get square by index on board
    Square *getSquare1(int index);
    Square *getSquare1(std::string property);
    std::vector<std::shared_ptr<Square>> getBoard();
};

#endif


