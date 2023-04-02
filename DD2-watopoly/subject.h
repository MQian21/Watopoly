#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <vector>

class Subject
{
    std::vector<Observer *> observers;

public:
    Subject();
    virtual ~Subject() = 0;
    void attach(Observer *o);
    void attachV2(Observer *o);
    void notifyObservers();
    void attachObservers(Subject *s);
    virtual void attachSquares(Observer *o);
    virtual void attachPlayers(Observer *o);
};

#endif

