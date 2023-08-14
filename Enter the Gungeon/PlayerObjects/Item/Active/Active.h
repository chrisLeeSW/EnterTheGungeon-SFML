#pragma once
#include "Item.h"

class Active : public Item
{

public:

    enum class Types
    {
        PilotActive,
        PrisonerActive,
    };



protected:



public:

    bool isUsingActiveSkill = false;
   // Types type = Types::Active;

    Active(const std::string& textureId = "", const std::string& n = "");
    virtual ~Active() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

};

