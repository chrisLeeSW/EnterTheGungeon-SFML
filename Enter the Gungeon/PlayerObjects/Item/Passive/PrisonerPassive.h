#pragma once
#include "Passive.h"
#include "AnimationController.h"

class Player;

class PrisonerPassive : public Passive
{

protected:
    AnimationController animation;

    Player* player = nullptr;

    bool isPassiveOn = false;
    bool onePlay = true;


public:

    Item::Types itemtype = Item::Types::PrisonerPassive;
    Item::WAP wap = Item::WAP::Passive;

    PrisonerPassive(const std::string& textureId = "", const std::string& n = "");
    virtual ~PrisonerPassive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    virtual Item::Types GetItemType() { return itemtype; }
    virtual Item::WAP GetItemWAP() { return wap; }
};

