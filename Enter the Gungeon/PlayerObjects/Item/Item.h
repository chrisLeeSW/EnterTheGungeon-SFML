#pragma once
#include"SpriteGo.h"
#define DEGREES_90 90.0f

class Player;

class Item : public SpriteGo
{

public:

    enum class WAP
    {
        None,
        Weapon,
        Active,
        Passive,
    };

    enum class Types
    {
        None,
        PilotWeapon,
        PilotPassive,
        PilotActive,
        PrisonerWeapon,
        PrisonerPassive,
        PrisonerActive,
        Pad,
        BulletTime,
        ShotGun,
    };


protected:

    Player* player;

    sf::Vector2f mousePos;
    sf::Vector2f look;

public:

    Item::WAP wap;
    Item::Types type;

    Item(const std::string& textureId = "", const std::string& n = "");
    virtual ~Item() override { Release(); }

    virtual void Init() =0;
    virtual void Reset()=0;
    virtual void Update(float dt) =0;
    
    virtual Item::Types GetItemType();
    virtual Item::WAP GetItemWAP();
};


