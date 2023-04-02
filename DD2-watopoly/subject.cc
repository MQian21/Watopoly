#include "subject.h"
#include <iostream>

#include "player.h"

using namespace std;

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer *o)
{
    observers.emplace_back(o); // Attach viewboard to game
    attachSquares(o);          // Attach viewboard to all players and squares
    attachPlayers(o);
}

void Subject::attachV2(Observer *o)
{
    observers.emplace_back(o);
}

void Subject::attachObservers(Subject *s)
{
    for (auto it = observers.begin(); it != observers.end(); it++)
    {
        s->attach(*it);
    }
}

void Subject::notifyObservers()
{
    for (auto ob : observers)
    {
        ob->notify(this);
    }
}

void Subject::attachSquares(Observer *o) {}
void Subject::attachPlayers(Observer *o) {}
