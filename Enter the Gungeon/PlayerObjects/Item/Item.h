#pragma once
#include"SpriteGo.h"
#define DEGREES_90 90.0f

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

    virtual void Init() =0;
    virtual void Release()=0;
    virtual void Reset()=0;

    virtual void Update(float dt) =0;
    virtual void Draw(sf::RenderWindow& window) =0;
    

};


