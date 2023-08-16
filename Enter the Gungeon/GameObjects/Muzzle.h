#pragma once
#include "GameObject.h"

class Muzzle : public GameObject
{
public:
	bool isBlink = false;
	sf::Vector2f direction;
	float speed = 0.f;
	float range = 1000.f;
	float delay = 0.f;
	int quantity = 1;
	float interval = 0.f;

	bool isEdit = true;

protected:
	bool isPlay = false;
	float innerdelay = 0.f;
	float innerinterval = 0.f;
	int innerquantity = 0;

public:
	sf::CircleShape circle;

	Muzzle(const std::string& n = "");
	virtual ~Muzzle() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Play();
};