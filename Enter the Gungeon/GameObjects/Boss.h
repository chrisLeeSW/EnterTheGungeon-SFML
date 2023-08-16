#pragma once
#include "Enemy.h"
#include "AnimationController.h"

class Player;

class Boss : public Enemy
{
protected:

public:
	Boss(EnemyTypes type, const std::string& textureId = "", const std::string& n = "");
	virtual ~Boss() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};