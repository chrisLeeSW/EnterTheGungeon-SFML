#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "Weapon.h"
#include "Passive.h"
#include "Active.h"


class Item;
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

	std::string clipId;

	AnimationController animation;

	bool isGame = false;
	bool isLobby = true;

	//�����Բ�
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	sf::Vector2f windowsize;

	//�÷��̾� ��
	SpriteGo* hand;
	bool handflipX = false;

	//�������� ������
	std::vector<Passive*> passiveList;
	Active* active = nullptr;


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

	Types type;

	bool playerchoise = false;

public:

	Player(Types type, const std::string& textureId = "", const std::string& n = "");
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


	void ChangePlayer(sf::Vector2f pos,bool choise);

	void SetSceneGame();

	void GetItem(Item::Types type);

	sf::Vector2f GetDir() { return direction,position; }

};