#pragma once
#include "SpriteGo.h"

class Player;

class Chest : public SpriteGo
{
protected:
	AnimationController animation;

	bool interaction = false;
	bool isOpened = false;

	Player* player;

public:
	Chest();
	virtual ~Chest() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};