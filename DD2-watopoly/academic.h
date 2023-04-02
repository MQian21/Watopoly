#ifndef ACADEMIC_H
#define ACADEMIC_H
#include "ownable.h"
#include "player.h"
#include <map>


class Academic : public Ownable
{
    static std::map<std::string, int> monopolyBlock;
    int improvementCost;
    int improvementCount;
    std::string blockKey; // Look up blockKey in map to see if monopoly
    std::vector<int> improvementTuition;

public:
    Academic(std::string name, int index, int cost, int improvementCost, std::string blockKey, std::vector<int> improvementTuition);
    void action(Player *p) override;
    bool getIsMonopoly(Player *p);
    int getImprovementCount();
    int getImprovementCost();
    void buyImprovement();
    void sellImprovement();
    void setImprovement(int amount);
};

#endif
