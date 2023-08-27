#pragma once
#include "SpriteGo.h"
#include "Weapon.h"



class DropEquipItem : public SpriteGo
{

protected:

	Weapon::Types type = Weapon::Types::None;
    Player* player;

public:

    DropEquipItem(const std::string& textureId = "", const std::string& n = "");
    virtual ~DropEquipItem() override { Release(); }

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;

    void SetType(Weapon::Types type);

    std::function<void()> OnBump;

};

