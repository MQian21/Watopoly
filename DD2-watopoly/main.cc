#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include "controller.h"
#include "viewboard.h"
#include "game.h"

using namespace std;

void usage()
{
    cerr << "Incorrect Arguments" << endl;
    cerr << "./watopoly <-load file> <-testing>" << endl;
}

int main(int argc, char **argv)
{
    bool isNewGame = true;

    if (argc > 4)
    {
        usage();
        return 1;
    }

    // normal mode
    if (argc == 1)
    {
        Game game{};
        ViewBoard view{&game};
        Controller controller{&game, &view, isNewGame};
        controller.play(false);
    }

    // testing mode
    else if (argc == 2)
    {
        if ((strcmp(argv[1], "-testing")) != 0)
        {
            usage();
            return 1;
        }
        else
        {
            Game game{};
            ViewBoard view{&game};
            Controller controller{&game, &view, isNewGame};
            controller.play(true);
        }
    }

    else if (argc == 3)
    {
        if ((strcmp(argv[1], "-load")) != 0)
        {
            cout << argv[1] << endl;
            usage();
            return 1;
        }
        else
        {
            isNewGame = false;
            Game game{};
            ViewBoard view{&game};
            Controller controller{&game, &view, isNewGame};
            controller.loadGame(&game, &view, argv[2]);
            controller.play(false);
        }
    }

    else if (argc == 4)
    {
        isNewGame = false;
        Game game{};
        ViewBoard view{&game};
        Controller controller{&game, &view, isNewGame};
        controller.play(true);
    }
}

