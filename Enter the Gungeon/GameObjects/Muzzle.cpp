#include "stdafx.h"
#include "Muzzle.h"
#include "SceneBulletEditor.h"

#include "EnemyBullet.h"

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

		EnemyBullet* bullet = new EnemyBullet();
		bullet->SetBullet(isBlink);
		bullet->SetPosition(position);
		bullet->Shoot(direction, speed, range);
		bullet->Init();
		bullet->Reset();

		SceneBulletEditor* scene = (SceneBulletEditor*)SCENE_MGR.GetCurrScene();
		scene->AddGo(bullet);

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
