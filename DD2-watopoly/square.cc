#include "square.h"
#include "game.h"
#include <vector>
#include <string>

using namespace std;

Square::Square(string name, int index) : Subject{}, name{name}, index{index}
{
}

void Square::action(Player *p)
{
    cout << "It's time to take action on " << name << endl;
}

string Square::getName()
{
    return name;
}

int Square::getIndex()
{
    return index;
}

Square::~Square() {}

