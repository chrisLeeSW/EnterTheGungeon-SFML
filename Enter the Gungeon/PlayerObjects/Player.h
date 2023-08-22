#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "Weapon.h"
#include "Passive.h"
#include "Active.h"


class Item;
class Scene;
class Bullet;
class PlayerUI;

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

	enum class State
	{
		Idle,
		Hit,
		Roll,
		Walk,
		Relode
	};


protected:

	sf::Vector2f windowsize;

	//Animation
	AnimationController animation;
	AnimationController actEffect;
	AnimationController blankBullet;

	//BlankBullet
	sf::CircleShape blankEffect;
	bool isBlank = false;
	bool isBlankEffect = false;
	bool isBlankAnimation = false;



	//Player Move
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	std::string clipId;

	int currentIndex = 0;



	//플레이어 손



	//아이템
	std::vector<Passive*> passiveList;
	std::vector<Weapon*> weaponList;
	Active* active = nullptr;



	//플레이어 셋팅
	Types type;
	float speed;
	float rollspeed;
	int maxHp = 6;
	int blankBulletCount = 0;
	float hitDelay = 1.0f;
	bool isGame = false;
	bool isLobby = true;

	int hp;

	float effect = 0.f;

	float currenthitDelay = 0.f;

	//플레이어 상태



	bool isAlive = true;
	bool iswalk = false;
	bool isrolling = false;
	bool isHit = false;
	bool isSceneGame = false;
	bool flipX = false;

	bool playerchoise = false;


	sf::Vector2f look;
	float angle;
	float magnitude;


	//UI
	SpriteGo* ouch;
	sf::Color ouchoriginalColor;
	sf::Color originalColor;
	sf::Sprite shadow;
	PlayerUI* playerUI;

	sf::Vector2f handPos{ 7.f,-6.f };
	SpriteGo* hand;
	bool handflipX = false;


	//Enemy
	std::list<Enemy*> enemylist;



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




public:

	sf::Sprite walk;
	sf::Sprite blanksprite;
	
	sf::Vector2f playerhand;
	bool isUsingActiveSkill = false;

	Player(Types type, const std::string& textureId = "", const std::string& n = "");
	virtual ~Player() override { Release(); }

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	void OnPlayerHit();

	void OnDeathPlayer();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerRotation();
	void BlankBullet(float dt);
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
	bool IsAlive() { return isAlive; }
	bool IsHit() { return isHit; }
	bool IsBlankBullet() { return isBlank; }
	void SetBalnkBUllet(bool blank) { isBlank = blank; }

	void SetPlayerUI(PlayerUI* playerui) { playerUI = playerui; }


	sf::Vector2f PlayerHandPos() { return hand->GetPosition(); }
	int GetHp() { return hp; }

	void SetEnemyList(std::list<Enemy*> enemylist);

	//skill
	Weapon* GetCurrenWeapon() { return weaponList[currentIndex]; }
	
};