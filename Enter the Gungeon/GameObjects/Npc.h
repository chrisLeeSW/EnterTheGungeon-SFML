#pragma once
#include "SpriteGo.h"

class Player;

class Npc : public SpriteGo
{
public:
	enum class NpcType
	{
		None = -1,

		ShopOwner,

		Count,
	};

protected:
	AnimationController animation;
	Npc::NpcType type;
	Player* player;

	sf::RectangleShape box;
	sf::Text text;
	std::string speech = "";

	float duration = 1.5f;
	float timer = 0.f;

public:
	Npc(Npc::NpcType type);
	virtual ~Npc() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetOrigin(Origins origin) override;

	void SetSpeech();
};