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
	};


protected:

	ObjectPool<Weapon> poolWeapons;
	std::string clipId;

	AnimationController animation;

	//선생님꺼
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	sf::Vector2f windowsize;

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


	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerRotation();
	void SetFlipX(bool filp);
	void PlayerAct(float dt);

	sf::Vector2f GetPlayerPos();
	void SetPlayerChoise(bool playerchoise);

	void ChoisePlayer(Types type);
	void ChangePlayer(sf::Vector2f pos,bool choise);

	Types GetType();

	bool GetPlayerchoise();

};

