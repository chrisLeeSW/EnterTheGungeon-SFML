#pragma once
#include "Item.h"


class Passive : public Item
{

protected:




public:

    Types type = Types::Passive;

    Passive(const std::string& textureId = "", const std::string& n = "");
    virtual ~Passive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

};

