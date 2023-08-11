#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"

class Player;
class Bullet;

class GameObject;

class Weapon : public SpriteGo
{
public:

	enum class Types
	{
		None,
		PilotWeapon,
		PrisonerWeapon,
		Ak47,
	};

protected:

	Bullet* bullet;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

	sf::Vector2f mousePos;
	sf::Vector2f look;

	AnimationController animation;

	std::vector<AnimationController> shootEffect;

	Player* player;

	Types weaponType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	float reload;
	int santan;

	sf::Vector2f handPos;

public:

	Weapon(const std::string& textureId = "", const std::string& n = "");
	//Weapon(Types type);
	virtual ~Weapon() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPlayer(Player* player);
	virtual void Shoot(Weapon::Types type);
	virtual void SetType(Types t);
	virtual void SetGunFlipx(bool flip) = 0;



	//sf::Vector2f ScreenToWorldPos(sf::Vector2f screenPos);
	//sf::Vector2f ScreenToUiPos(sf::Vector2f screenPos);
	//sf::Vector2f WorldPosToScreen(sf::Vector2f worldPos);
	//sf::Vector2f UiPosPosToScreen(sf::Vector2f uiPos);


	//¾È¾µµí?
	//template<typename T>
	//T AddWeapon(T weapon)
	//{
	//	T* addweapon = &weapon
	//	Scene* scene = SCENE_MGR.GetGameScene();
	//	SceneGame* SG = dynamic_cast<SceneGame*>(scene);

	//	addweapon = (T*)SG->AddGo(new T());
	//}
};