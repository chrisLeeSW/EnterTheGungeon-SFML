#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "Weapon.h"

class Scene;

class Player : public SpriteGo
{
public:

	struct ClipInfo
	{
		std::string idle;
		std::string walk;
		std::string roll;
		bool flipX = false;
		sf::Vector2f point;
	};

	enum class Types
	{
		Pilot,
		Prisoner,
		WeaponPilot,
		WeaponPrisoner,
	};


protected:

	//ObjectPool<Weapon> poolWeapons;
	std::string clipId;

	AnimationController animation;

	bool isGame = false;
	bool isLobby = true;

	//선생님꺼
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	sf::Vector2f windowsize;

	//플레이어 손
	SpriteGo* hand;
	bool handflipX = false;


	//플레이어 움직임
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

	Types type;

	bool playerchoise = false;

public:
	Player(Types type, const std::string& textureId = "", const std::string& n = "");
	Player(const std::string& textureId = "", const std::string& n = "");
	virtual ~Player() override { Release(); }

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerRotation();
	void SetFlipX(bool filp);
	void PlayerAct(float dt);

	sf::Vector2f GetPlayerPos();

	void ChangePlayer(sf::Vector2f pos,bool choise);

	Types GetType();

	void SetSceneGame();
	void AddWeapon();
};