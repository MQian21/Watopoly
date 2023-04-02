#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "ownable.h"

class Residence : public Ownable
{

public:
    Residence(std::string name, int index, int cost);
    virtual void action(Player *p) override;
};

#endif

