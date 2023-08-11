#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "SceneGame.h"
#include "Scene.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "GameObject.h"

Weapon::Weapon(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Weapon::Init()
{

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotShoot.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);



	//ObjectPool<Bullet>* ptr = &poolBullets;
	//poolBullets.OnCreate = [ptr](Bullet* bullet) {
	//	bullet->pool = ptr;
	//};
	//poolBullets.Init();


}

void Weapon::Release()
{
}

void Weapon::Reset()
{
	SpriteGo::Reset();

	SetOrigin(Origins::MR);
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

void Weapon::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;

	//불릿 ID까지 스트링으로 받아와서 애니메이션 animation.Play(" 요기  ") <- 넣어버리기
}
