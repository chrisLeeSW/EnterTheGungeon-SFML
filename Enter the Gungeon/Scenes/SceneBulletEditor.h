#pragma once
#include "Scene.h"

class Muzzle;

class SceneBulletEditor : public Scene
{
protected:
	Muzzle* curMuzzle = nullptr;
	std::list<Muzzle*> muzzlelist;

	std::string str = "";
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