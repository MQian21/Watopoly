#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "square.h"
#include "player.h"

class CollectOSAP : public Square
{
public:
    CollectOSAP(std::string name, int index);
    void action(Player *p) override;
};

#endif
