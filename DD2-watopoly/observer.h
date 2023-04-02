#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Subject;

class Observer
{
public:
    virtual ~Observer();
    virtual void notify(Subject *whoNotified) = 0; // pass the Subject that called the notify method
};

#endif

