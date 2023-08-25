#include "stdafx.h"
#include "BossUI.h"
#include "Boss.h"
#include "DataTableMgr.h"
#include "EnemyTable.h"
#include "StringTable.h"

BossUI::BossUI(const std::string& n)
	:GameObject(n)
{
	
}

BossUI::~BossUI()
{
	Release();
}

void BossUI::SetPosition(const sf::Vector2f& p)
{
	SetPosition(p.x, p.y);
}

void BossUI::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	bar.setPosition(x, y);
	float diff = bar.getLocalBounds().width * 0.5f;
	innerbar.setPosition(x - diff + 17.f, y);
	name.setPosition(x - diff, y - 10.f);
}

void BossUI::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	Utils::SetOrigin(bar, origin);
	Utils::SetOrigin(innerbar, Origins::ML);
	Utils::SetOrigin(name, Origins::BL);
}

void BossUI::Init()
{
	barAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/BossHp.csv"));
	barAnimation.SetTarget(&innerbar);
}

void BossUI::Release()
{
}

void BossUI::Reset()
{
	barAnimation.Play("Play");

	sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/GameUIAtlas.png");
	if (tex != nullptr)
	{
		bar.setTexture(*tex);
		bar.setTextureRect({ 288, 1021, 200, 13 });
	}

	sf::Font* font = RESOURCE_MGR.GetFont("fonts/PF.ttf");
	if (font != nullptr)
	{
		name.setFont(*font);
		name.setCharacterSize(30);
	}

	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable »ç¿ë
	std::wstring bossname;
	switch (boss->GetType())
	{
	case Enemy::EnemyName::GatlingGull:
		bossname = table->GetW("GATLING_GULL");
		break;
	}

	name.setString(bossname);
	name.setScale(0.3f,0.3f);
	SetOrigin(origin);
	SetPosition(position);
	hp = maxHp;

	innerbar.setScale(1.f, 1.f);
}

void BossUI::Update(float dt)
{
	barAnimation.Update(dt);
}

void BossUI::Draw(sf::RenderWindow& window)
{
	window.draw(bar);
	window.draw(innerbar);
	window.draw(name);
}

void BossUI::SetBoss(Boss* boss)
{
	this->boss = boss;
	const EnemyInfo* info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(boss->GetType());

	this->maxHp = info->maxHp;
}

void BossUI::Renew()
{
	hp = boss->GetHp();
	innerbar.setScale(hp / maxHp, 1.f);

	if (hp <= 0.f)
	{
		SetActive(false);
	}
}
