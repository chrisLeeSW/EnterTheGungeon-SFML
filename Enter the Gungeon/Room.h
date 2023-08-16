#pragma once
#include "GameObject.h"
class Room :public GameObject
{

public :

	Room( const std::string& n = "");
	virtual ~Room() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

