#pragma once
#include "Active.h"
#include "AnimationController.h"

class Player;

class PrisonerActive : public Active
{

protected:
    AnimationController animation;

    Player* player = nullptr;

    sf::Vector2f dir;
    sf::Vector2f pos;

public:

    PrisonerActive(const std::string& textureId = "", const std::string& n = "");
    virtual ~PrisonerActive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;


};

