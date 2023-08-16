#pragma once
#include"SpriteGo.h"

class Player;
class Weapon;

class Item : public SpriteGo
{

public:

    enum class Types
    {
        None,
        Passive,
        Active,
        Weapon,
    };


protected:

    std::unordered_map<std::string, Item*> items;

    Player* player;
    Weapon* weapon;

    sf::Vector2f mousePos;
    sf::Vector2f look;

public:

    Types type;

    Item(const std::string& textureId = "", const std::string& n = "");
    virtual ~Item() override { Release(); }

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
};


