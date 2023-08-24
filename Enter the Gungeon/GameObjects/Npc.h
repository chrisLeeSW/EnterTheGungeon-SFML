#pragma once
#include "SpriteGo.h"

class Player;

class Npc : public SpriteGo
{
public:
	enum class NpcType
	{
		None = -1,

		ShowOwner,

		Count,
	};

protected:
	AnimationController animation;
	Npc::NpcType type;

public:
	Npc(Npc::NpcType type);
	virtual ~Npc() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};