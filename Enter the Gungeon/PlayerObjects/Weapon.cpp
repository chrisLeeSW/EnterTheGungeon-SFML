#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "SceneGame.h"
#include "Scene.h"

Weapon::Weapon(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Weapon::Init()
{

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotShoot.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);



	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->pool = ptr;
	};
	poolBullets.Init();


}

void Weapon::Release()
{
}

void Weapon::Reset()
{
	SpriteGo::Reset();

	SetOrigin(Origins::MR);
	animation.Play("Shoot");
}

void Weapon::Update(float dt)
{
	animation.Update(dt);

	SetPosition(player->GetPlayerPos());
	SetOrigin(Origins::BL);
	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));


	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	//{
	//	WEAPON_MGR.ChangeCurrentWeapon((int)Types::PilotGun);
	//}
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	//{
	//	WEAPON_MGR.ChangeCurrentWeapon((int)Types::PilotGun);
	//}

	if(INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		Shoot(WEAPON_MGR.GetCurrentWeapon());
	}

}

void Weapon::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Weapon::SetPlayer(Player* player)
{
	this->player = player;
}

void Weapon::Shoot(Weapon::Types type)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	Bullet* bullet = poolBullets.Get();


	bullet->Fire(GetPosition(), look);
	bullet->SetType((int)type);

	if (scene != nullptr)
	{
		//bullet->SetMonsterList(sceneDev1->GetMonsterList());
		sceneGame->AddGo(bullet);
	}
}