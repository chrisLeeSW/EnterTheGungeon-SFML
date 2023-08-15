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

protected:

	std::string clipId;

	AnimationController animation;
	AnimationController actEffect;


	bool isGame = false;
	bool isLobby = true;

	//선생님꺼
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	sf::Vector2f windowsize;

	//플레이어 손
	SpriteGo* hand;
	bool handflipX = false;

	//아이템
	std::vector<Passive*> passiveList;
	std::vector<Weapon*> weaponList;
	Active* active = nullptr;

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
	float effect = 0.f;
	bool iswalk = false;
	sf::Vector2f look;

	Types type;

	bool playerchoise = false;

	std::unordered_map<sf::Keyboard::Key, int> keyToIndexMap = {
	{sf::Keyboard::Num1, 1},
	{sf::Keyboard::Num2, 2},
	{sf::Keyboard::Num3, 3},
	{sf::Keyboard::Num4, 4},
	{sf::Keyboard::Num5, 5},
	{sf::Keyboard::Num6, 6},
	{sf::Keyboard::Num7, 7},
	{sf::Keyboard::Num8, 8},
	{sf::Keyboard::Num9, 9},
	};


	int currentIndex = 0;


	sf::Vector2f handPos{ 7.f,-6.f };

public:

	sf::Sprite walk;
	
	sf::Vector2f playerhand;
	bool isUsingActiveSkill = false;

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


	void ChangePlayer(sf::Vector2f pos, bool choise);

	void SetSceneGame();

	void SwapWeapon();
	void GetItem(Passive::Types type);
	void GetItem(Active::Types type);
	void GetItem(Weapon::Types type);

	bool GetFilpX() { return flipX; }
	bool isRolling() { return isrolling; }


	sf::Vector2f PlayerHandPos() { return hand->GetPosition(); }
};