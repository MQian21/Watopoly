#include "board.h"
#include "game.h"
#include "academic.h"

using namespace std;

Board::Board(Game *g) : game{g}, gameBoard{
                                     vector<shared_ptr<Square>>{

                                         make_shared<CollectOSAP>("COLLECT OSAP", 0),
                                         make_shared<Academic>("AL", 1, 40, 50, "Arts1", vector<int>{2, 10, 30, 90, 160, 250}),
                                         make_shared<SLC>("SLC", 2),
                                         make_shared<Academic>("ML", 3, 60, 50, "Arts1", vector<int>{4, 20, 60, 180, 320, 450}),
                                         make_shared<Tuition>("TUITION", 4),
                                         make_shared<Residence>("MKV", 5, 200),
                                         make_shared<Academic>("ECH", 6, 100, 50, "Arts2", vector<int>{6, 30, 90, 270, 400, 550}),
                                         make_shared<NeedlesHall>("NEEDLES HALL", 7),
                                         make_shared<Academic>("PAS", 8, 100, 50, "Arts2", vector<int>{6, 30, 90, 270, 400, 550}),
                                         make_shared<Academic>("HH", 9, 120, 50, "Arts2", vector<int>{8, 40, 100, 300, 450, 550}),
                                         make_shared<TimsLine>("DC TIMS LINE", 10, game),
                                         make_shared<Academic>("RCH", 11, 140, 100, "Eng", vector<int>{10, 50, 150, 450, 625, 750}),
                                         make_shared<Gym>("PAC", 12, 150),
                                         make_shared<Academic>("DWE", 13, 140, 100, "Eng", vector<int>{10, 50, 150, 450, 625, 750}),
                                         make_shared<Academic>("CPH", 14, 160, 100, "Eng", vector<int>{12, 60, 180, 500, 700, 900}),
                                         make_shared<Residence>("UWP", 15, 200),
                                         make_shared<Academic>("LHI", 16, 180, 100, "Health", vector<int>{14, 70, 200, 550, 750, 950}),
                                         make_shared<SLC>("SLC", 17),
                                         make_shared<Academic>("BMH", 18, 180, 100, "Health", vector<int>{14, 70, 200, 550, 750, 950}),
                                         make_shared<Academic>("OPT", 19, 200, 100, "Health", vector<int>{16, 80, 220, 600, 800, 1000}),
                                         make_shared<GooseNesting>("GOOSE NESTING", 20),
                                         make_shared<Academic>("EV1", 21, 220, 150, "Env", vector<int>{18, 90, 250, 700, 875, 1050}),
                                         make_shared<NeedlesHall>("NEEDLES HALL", 22),
                                         make_shared<Academic>("EV2", 23, 220, 150, "Env", vector<int>{18, 90, 250, 700, 875, 1050}),
                                         make_shared<Academic>("EV3", 24, 240, 150, "Env", vector<int>{20, 100, 300, 750, 925, 1100}),
                                         make_shared<Residence>("V1", 25, 200),
                                         make_shared<Academic>("PHYS", 26, 260, 150, "Sci1", vector<int>{22, 110, 330, 800, 975, 1150}),
                                         make_shared<Academic>("B1", 27, 260, 150, "Sci1", vector<int>{22, 110, 330, 800, 975, 1150}),
                                         make_shared<Gym>("CIF", 28, 150),
                                         make_shared<Academic>("B2", 29, 280, 150, "Sci1", vector<int>{24, 120, 360, 850, 1025, 1200}),
                                         make_shared<GoTims>("GO TO TIMS", 30),
                                         make_shared<Academic>("EIT", 31, 300, 200, "Sci2", vector<int>{26, 130, 390, 900, 1100, 1275}),
                                         make_shared<Academic>("ESC", 32, 300, 200, "Sci2", vector<int>{26, 130, 390, 900, 1100, 1275}),
                                         make_shared<SLC>("SLC", 33),
                                         make_shared<Academic>("C2", 34, 320, 200, "Sci2", vector<int>{28, 150, 450, 1000, 1200, 1400}),
                                         make_shared<Residence>("REV", 35, 200),
                                         make_shared<NeedlesHall>("NEEDLES HALL", 36),
                                         make_shared<Academic>("MC", 37, 350, 200, "Math", vector<int>{35, 175, 500, 1100, 1300, 1500}),
                                         make_shared<CoopFee>("COOP FEE", 38),
                                         make_shared<Academic>("DC", 39, 400, 200, "Math", vector<int>{50, 200, 600, 1400, 1700, 2000})}}

{
}

Square &Board::getSquare(string name)
{
    Square &s = *gameBoard.begin()->get();
    for (auto &i : gameBoard)
    {
        if (name == i->getName())
        {
            s = *i;
            break;
        }
    }
    return s;
}

Square &Board::getSquare(int index)
{
    Square &s = *(gameBoard.begin() + index)->get();
    return s;
}

// Returns a Square* buy by index
Square *Board::getSquare1(int index)
{
    Square *s = (gameBoard.begin() + index)->get();
    return s;
}

// Returns a Square* but buy property name
Square *Board::getSquare1(string property)
{
    for (int i = 0; i < 40; i++)
    {
        string name = (gameBoard.begin() + i)->get()->getName();
        if (property == name)
        {
            return (gameBoard.begin() + i)->get();
        }
    }
    return nullptr;
}
