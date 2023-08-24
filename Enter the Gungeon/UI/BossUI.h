#pragma once
#include "GameObject.h"

class Boss;

class BossUI : public GameObject
{
protected:
	AnimationController barAnimation;

	sf::Sprite bar;
	sf::Sprite innerbar;
	sf::Text name;
	Boss* boss;

	float maxHp = 0.f;
	float hp = 0.f;

public:
	BossUI(const std::string& n = "");
	virtual ~BossUI() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetBoss(Boss* boss);
	void Renew();
};