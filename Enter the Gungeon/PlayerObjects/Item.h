#pragma once
#include "Player.h"

//struct IntemInfo
//{
//    Item::IntemType itemtype;
//    int speed;
//    float damage;
//    int range;
//    int knockback;
//};

class Item : public Player
{

public:

    
    enum class IntemType
    {
        None,
        PilotPassive,
        PilotActive,
        PrisonerPassvie,
        PrisonerActive,
    };

protected:

    std::unordered_map<std::string, Item*> items;

public:


};


