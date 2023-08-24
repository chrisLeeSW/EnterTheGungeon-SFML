#pragma once
#include "SpriteGo.h"

class Player;

class DisplayItem :	public SpriteGo
{
public:
    enum class Names
    {
        None = -1,

        Heart,
        Hearts,
        Key,
        Blank,
        Ammo,

        Count,
    };

protected:
	int price = 0;
	bool interaction = false;

    DisplayItem::Names item;
    sf::RectangleShape box;
    sf::Text text;
    Player* player;

public:
    DisplayItem(DisplayItem::Names item, const std::string& textureId = "", const std::string& n = "");
    virtual ~DisplayItem() override { Release(); }

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    virtual void SetPosition(const sf::Vector2f& p) override;
    virtual void SetPosition(float x, float y) override;

    virtual void SetOrigin(Origins origin);

    std::function<void()> action;
};