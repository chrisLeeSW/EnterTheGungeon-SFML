#pragma once
#include "Active.h"
#include "AnimationController.h"



class PilotActive : public Active
{

protected:

    AnimationController animation;

public:

    
    PilotActive(const std::string& textureId = "", const std::string& n = "");
    virtual ~PilotActive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;


};

