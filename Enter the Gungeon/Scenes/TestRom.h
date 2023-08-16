#pragma once
#include "Scene.h"
class TestRom : public Scene
{
protected:

public :
	TestRom();
	virtual ~TestRom() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

