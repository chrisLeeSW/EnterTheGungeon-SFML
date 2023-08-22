#pragma once

#include "Item.h"

class DropItem : public Item
{
protected:

    enum class Types
    {
        ź��,
        ����ź,
        ����,
        ü��,
        źâ,
        ��Ը��ũ����,
    };

public:

    DropItem(const std::string& textureId = "", const std::string& n = "");
    virtual ~DropItem() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

};

