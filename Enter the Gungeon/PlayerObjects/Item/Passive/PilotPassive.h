#pragma once
#include "Passive.h"

class PilotPassive : public Passive
{

protected:


public:

    Item::Types itemtype = Item::Types::PilotPassive;
    Item::WAP wap = Item::WAP::Passive;

    PilotPassive(const std::string& textureId = "", const std::string& n = "");
    virtual ~PilotPassive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    virtual Item::Types GetItemType() { return itemtype; }
    virtual Item::WAP GetItemWAP() { return wap; }
};

