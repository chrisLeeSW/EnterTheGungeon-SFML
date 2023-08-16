#include "stdafx.h"
#include "Magnum.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Enemy.h"

Magnum::Magnum(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::Magnum);


	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);

	//SetScale(0.5f,0.5f);

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(1.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

}

void Magnum::Init()
{
	//gun.Play("Idle");
}

void Magnum::Release()
{
}

void Magnum::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Magnum::Update(float dt)
{
		//Weapon::Update(dt);

		sf::Vector2f gunOffset1(16, -9);
		sf::Vector2f gunOffset2(16, 9);

		gun.Update(dt);
		SetPosition(enemy->GetPosition());

		//�������� ���� �� �̰� �ٵ� ������ �� �������� �÷��̾� �����������ϰ� ���������� �ϸ� 
		//�ѵ� �������� ������ ��� �� ������ ���� �� ó�� ��ġ�� ������ �Ǵµ�
		//�������� BL�� ���ϸ� ���� Rotation�Ҷ� ȸ���� ������ �� �����̰� �ƴ϶� �̻��ϰ� �� ������ Ȥ�� �ٸ� ����� �������?


		SetOrigin(Origins::BL);

		float angle = Utils::Angle(look);
		sf::Vector2f gunOffset = Utils::RotateVector(gunOffset1, angle, { 1, 0 });

		 //�̰� ���콺�ε� �÷��̾�� ���� ������ ���� ��ֶ������ؼ� �־�ߵɵ�
		if (flipX)
		{
			gunOffset = Utils::RotateVector(gunOffset2, angle, { 1, 0 });
			angle += FLIP_ANGLE_X;
		}

		sprite.setRotation(angle);

		//SetGunFlipx(player->GetFilpX());


		gunend.setPosition(gunPoint);
		gunPoint = enemy->GetPosition();
		gunPoint += gunOffset;

		//if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//{
		//	gun.Play("Shoot");
		//	WEAPON_MGR.Shoot(bulletType, gunPoint, look);
		//}
	}

void Magnum::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(gunend);
}

void Magnum::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Magnum::SetType(Weapon::Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	bulletType = (Bullet::Types)info->bulletType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}