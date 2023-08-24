#pragma once
#include "Active.h"

class TextGo;

class aBulletTime : public Active
{

protected:

    float duration = 1.f;
    bool isbullettime = true;

    TextGo* textbut;

public:

    Item::Types itemtype = Item::Types::BulletTime;
    Item::WAP wap = Item::WAP::Active;


    aBulletTime(const std::string& textureId = "", const std::string& n = "");
    virtual ~aBulletTime() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SetPlayer(Player* player) { this->player = player; }
};

