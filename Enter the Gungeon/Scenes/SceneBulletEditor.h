#pragma once
#include "Scene.h"

class EnemyBullet;

class SceneBulletEditor : public Scene
{
protected:
	EnemyBullet* curBullet = nullptr;

	sf::Vector2f direction;
	std::string str = "";

	std::list<EnemyBullet*> bulletlist;

	bool isPlay = false;

public:
	SceneBulletEditor();
	virtual ~SceneBulletEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	std::string InputString();
};