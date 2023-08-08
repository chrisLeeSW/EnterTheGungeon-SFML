#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "Weapon.h"

class Player :
	public SpriteGo
{
public:

	struct ClipInfo
	{
		std::string idle;
		std::string walk;
		std::string roll;
	};

	enum class PlayerAct
	{
		Idle,
		Walk,
		Roll
	};

protected:

	ObjectPool<Weapon> poolWeapons;
	PlayerAct playeract;
	std::string clipId;

	AnimationController animation;
	//�����Բ�
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	sf::Vector2f windowsize;

	//�÷��̾� ������
	sf::Vector2f velocity;
	sf::Vector2f direction;
	float speed;
	float rollspeed;
	bool isflip = false;
	bool flipX = false;
	bool isrolling = false;
	float angle;
	float magnitude;
	sf::Vector2f look;

public:
	Player(const std::string& textureId = "", const std::string& n = "");
	virtual ~Player() override { Release(); }


	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerRotation();
	void SetFlipX(bool filp);

	sf::Vector2f GetPlayerPos();
};

