#include "stdafx.h"
#include "Muzzle.h"
#include "SceneBulletEditor.h"
#include "SceneGame.h"
#include "EnemyBullet.h"
#include "Player.h"

Muzzle::Muzzle(const std::string& n)
	:GameObject(n)
{

}

Muzzle::~Muzzle()
{

}

void Muzzle::SetPosition(const sf::Vector2f& p)
{
	GameObject::SetPosition(p);
	circle.setPosition(p);
}

void Muzzle::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	circle.setPosition(x, y);
}

void Muzzle::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	Utils::SetOrigin(circle, origin);
}

void Muzzle::Init()
{
	circle.setRadius(5);
	if (isEdit) circle.setFillColor(sf::Color::White);

	SetOrigin(Origins::MC);
}

void Muzzle::Release()
{
}

void Muzzle::Reset()
{
	isPlay = false;

	innerdelay = 0.f;
	innerinterval = interval;
	innerquantity = 0;
}

void Muzzle::Update(float dt)
{
	if (!isPlay) return;

	innerdelay += dt;
	if (innerdelay < delay) return;

	if (innerquantity < quantity)
	{
		innerinterval += dt;
		if (innerinterval < interval) return;

		EnemyBullet* bullet;
		if (isEdit)
		{
			SceneBulletEditor* scene = (SceneBulletEditor*)SCENE_MGR.GetCurrScene();

			bullet = scene->GetPoolEnemyBullet().Get();

			scene->AddGo(bullet);
		}
		else
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();

			bullet = scene->GetPoolEnemyBullet().Get();
			bullet->SetPlayer(player);

			scene->AddGo(bullet);
		}
		
		bullet->SetBullet(isBlink);
		bullet->SetPosition(position);
		bullet->Shoot(direction, speed, range);
		bullet->Init();
		bullet->Reset();

		innerinterval = 0.f;
		innerquantity++;
	}
	else
	{
		Reset();
		if (isEdit) return;
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
	}
}

void Muzzle::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Muzzle::Play()
{
	isPlay = true;
}

void Muzzle::SetPlayer(Player* player)
{
	this->player = player;
}
