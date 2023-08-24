#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class Player;

class DropItem : public SpriteGo
{
public:

    enum class Types
    {
        None = -1,

        Shell1,
        Shell2,
        Heart,
        Hearts,
        Key,
        Blank,
        HegemonyCredit,

        Count,
    };

protected:

    AnimationController animation;
    DropItem::Types type = DropItem::Types::None;
    Player* player;

public:
    ObjectPool<DropItem>* pool;

    DropItem(const std::string& textureId = "", const std::string& n = "");
    virtual ~DropItem() override { Release(); }

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;

    void SetType(DropItem::Types type);
    void SetPlayer(Player* player);

    std::function<void()> OnBump;
};