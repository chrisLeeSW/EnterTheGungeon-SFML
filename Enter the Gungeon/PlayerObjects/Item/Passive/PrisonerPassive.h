#pragma once
#include "Passive.h"


class PrisonerPassive : public Passive
{

protected:



public:

    PrisonerPassive(const std::string& textureId = "", const std::string& n = "");
    virtual ~PrisonerPassive() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;


};

