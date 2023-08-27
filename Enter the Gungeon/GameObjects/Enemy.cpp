#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "EnemyTable.h"
#include "DataTableMgr.h"
#include "SceneGame.h"
#include "Muzzle.h"
#include "SpriteEffect.h"

//HaeJun
#include "EnemyShotGun.h"
#include "ItemMgr.h"
#include "Weapon.h"
#include "Magnum.h"
#include "Winchester.h"

Enemy::Enemy(EnemyName type, const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n), type(type)
{
	way.push_back({ 0.f, -1.f }); // Up
	way.push_back(Utils::Normalize({ 1.f, -1.f })); // LeftUp
	way.push_back({ 1.f, 0.f }); // Left
	way.push_back(Utils::Normalize({ 1.f, 1.f })); // LeftDown
	way.push_back({ 0.f, 1.f }); // Down

	SetOrigin(Origins::BC);
}

Enemy::~Enemy()
{
	Release();
}

void Enemy::Init()
{
	std::string name;
	switch (type)
	{
	case EnemyName::BulletKin:
		name = "BulletKin/BulletKin";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			OneShot(dir, speed);
		};
		break;
	case EnemyName::KeyBulletKin:
		name = "KeyBulletKin/KeyBulletKin";
		IfBump = []()
		{

		};
		IfDie = [this](sf::Vector2f dir)
		{
			state = Enemy::State::Bind;
			// Animation
			if (dir == way[0])
			{
				animation.Play("DieUp");
			}
			else if (dir == way[1])
			{
				animation.Play("DieLeftUp");
			}
			else if (dir == way[2])
			{
				animation.Play("DieLeft");
			}
			else if (dir == way[3])
			{
				animation.Play("DieLeftDown");
			}
			else if (dir == way[4])
			{
				animation.Play("DieDown");
			}

			IfBump = [this]()
			{
				player->AddKey(1);
				state = Enemy::State::Die;
				SetActive(false);
			};
		};
		break;
	case EnemyName::ShotgunKinRed:
		name = "ShotgunKinRed/ShotgunKinRed";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			ShotgunShot(dir, speed, 5, 15.f);
		};
		IfDie = [this](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 20); // table »ç¿ë
		};
		break;
	case EnemyName::ShotgunKinBlue:
		name = "ShotgunKinBlue/ShotgunKinBlue";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			if (patternCount < 1)
			{
				ShotgunShot(dir, speed, 5, 15.f);
				patternCount++;
			}
			else
			{
				ShotgunShot(dir, speed, 4, 10.f);
				patternCount = 0;
			}
		};
		IfDie = [this](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 33); // table »ç¿ë
		};
		break;
	default:
		std::cerr << "ERROR: Not Exist EnemyName (Enemy Init())" << std::endl;
		break;
	}

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieDown.csv"));

	animation.SetTarget(&sprite);
}

void Enemy::Reset()
{
	SpriteGo::Reset();
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Shadow.png");
		if (tex != nullptr)
		{
			shadow.setTexture(*tex);
			Utils::SetOrigin(shadow, Origins::MC);
		}
	}
	SetEnemy();

	state = Enemy::State::Idle;
	animation.Play("IdleDown");
	SetFlipX(false);
	SetOrigin(origin);

	hp = maxHp;
	attackTimer = attackInterval;
	patternCount = 0;

	//±èÇýÁØ Ãß°¡
	Scene* scene = SCENE_MGR.GetCurrScene();
	switch (type)
	{
	case EnemyName::BulletKin:
		weapon = (Magnum*)scene->AddGo(new Magnum());
		weapon->SetEnemy(this);
		break;
	case EnemyName::KeyBulletKin:
		state = Enemy::State::Runaway;
		break;
	case EnemyName::ShotgunKinRed:
		weapon = (EnemyShotGun*)scene->AddGo(new EnemyShotGun());
		weapon->SetEnemy(this);
		break;
	case EnemyName::ShotgunKinBlue:
		weapon = (Winchester*)scene->AddGo(new Winchester());
		weapon->SetEnemy(this);
		break;
	default:
		return;
		break;
	}
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	if (player == nullptr || state == Enemy::State::Die) return;
	if (PLAYER_MGR.IsPause()) return;

	direction = Utils::Normalize(player->GetPosition() - position);
	SetFlipX(direction.x > 0.f);
	float distance = Utils::Distance(player->GetPosition(), position);
	sf::Vector2f look = WhereWay(direction);
	if (attackTimer < attackInterval) attackTimer += dt;

	if (!wall.contains(position))
	{
		SetPosition(Utils::Clamp(position, { wallLeft, wallTop }, { wallRight, wallBottom }));
	}

	switch (state)
	{
	case Enemy::State::Idle:
		if (direction.x != 0.f || direction.y != 0.f)
		{
			state = Enemy::State::Move;
			return;
		}
		else
		{
			if (animation.GetCurrentClipId() != "IdleUp" && look == way[0])
			{
				animation.Play("IdleUp");
			}
			else if (animation.GetCurrentClipId() != "IdleLeftUp" && look == way[1])
			{
				animation.Play("IdleLeftUp");
			}
			else if (animation.GetCurrentClipId() != "IdleLeft" && look == way[2])
			{
				animation.Play("IdleLeft");
			}
			else if (animation.GetCurrentClipId() != "IdleLeftDown" && look == way[3])
			{
				animation.Play("IdleLeftDown");
			}
			else if (animation.GetCurrentClipId() != "IdleDown" && look == way[4])
			{
				animation.Play("IdleDown");
			}
		}
		break;
	case Enemy::State::Move:
		if (attackRange > distance)
		{
			state = Enemy::State::Attack;
			return;
		}

		if (animation.GetCurrentClipId() != "MoveUp" && look == way[0])
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftUp" && look == way[1])
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeft" && look == way[2])
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftDown" && look == way[3])
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" && look == way[4])
		{
			animation.Play("MoveDown");
		}
		SetPosition(position + direction * speed * dt);
		break;
	case Enemy::State::Attack:
		if (attackRange < distance - 100.f)
		{
			state = Enemy::State::Idle;
			return;
		}

		if (attackTimer >= attackInterval && isShoot) //±èÇýÁØ Ãß°¡
		{
			attackTimer = 0.f;
			if (IfShoot != nullptr)
			{
				IfShoot(direction, speed); //ÃÑ¾Ë ¼Óµµ ÁöÁ¤ ÇÊ¿ä

				// Animation
				if (look == way[0] && animation.GetCurrentClipId() != "AttackUp")
				{
					animation.Play("AttackUp");
				}
				else if (look == way[1] && animation.GetCurrentClipId() != "AttackLeftUp")
				{
					animation.Play("AttackLeftUp");
				}
				else if (look == way[2] && animation.GetCurrentClipId() != "AttackLeft")
				{
					animation.Play("AttackLeft");
				}
				else if (look == way[3] && animation.GetCurrentClipId() != "AttackLeftDown")
				{
					animation.Play("AttackLeftDown");
				}
				else if (look == way[4] && animation.GetCurrentClipId() != "AttackDown")
				{
					animation.Play("AttackDown");
				}
			}
			state = Enemy::State::Idle;
		}
		break;
	case Enemy::State::Hit:
		if (animation.AnimationEnd())
		{
			state = Enemy::State::Idle;
			return;
		}
		break;
	case Enemy::State::Die:
		return;
		break;
	case Enemy::State::Runaway:
		if (animation.GetCurrentClipId() != "MoveUp" && look == way[0])
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftUp" && look == way[1])
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeft" && look == way[2])
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftDown" && look == way[3])
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" && look == way[4])
		{
			animation.Play("MoveDown");
		}
		direction = -direction;
		SetFlipX(direction.x > 0.f);
		SetPosition(position + direction * speed * dt);
		break;
	case Enemy::State::Skill:
		if (animation.AnimationEnd()) state = Enemy::State::Idle;
		break;
	case Enemy::State::Bind:
		break;
	case Enemy::State::Count:
		std::cout << "WARNING: Wrong State (Enemy Update(dt))" << std::endl;
		state = Enemy::State::Idle;
		break;
	default:
		break;
	}

	if (player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) // Collider Ãæµ¹·Î º¯°æ ¿ä±¸
	{
		if (IfBump != nullptr)
		{
			IfBump();
		}
		else
		{
			OnBump();
		}
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(shadow);
	SpriteGo::Draw(window);
}

void Enemy::SetPosition(const sf::Vector2f& p)
{
	shadow.setPosition(p);
	SpriteGo::SetPosition(p);
}

void Enemy::SetPosition(float x, float y)
{
	shadow.setPosition(x, y);
	SpriteGo::SetPosition(x, y);
}

void Enemy::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

const float& Enemy::GetHp()
{
	return hp;
}

const bool Enemy::IsAlive() const
{
	return (state == Enemy::State::Die);
}

sf::Vector2f Enemy::WhereWay(sf::Vector2f dir)
{
	sf::Vector2f result;
	float minf = 1.f;
	for (auto it : way)
	{
		float diff = Utils::Distance({ abs(dir.x), dir.y }, it);
		if (diff <= minf)
		{
			minf = diff;
			result = it;
		}
	}
	return result;
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

void Enemy::SetEnemy()
{
	const EnemyInfo* info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(type);

	this->maxHp = info->maxHp;
	this->speed = info->speed;
	this->attackRange = info->attackRange;
	this->attackInterval = info->attackInterval;
	this->superarmor = info->superarmor;
}

void Enemy::LoadMuzzle(const std::string& path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();

	for (int i = 1; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<std::string>(i);
		Muzzle* muzzle = (Muzzle*)scene->AddGo(new Muzzle());

		muzzle->isBlink = (bool)std::stoi(rows[1]);
		{
			std::string temp;
			std::stringstream ss(rows[2]);
			std::vector<float> values;
			while (std::getline(ss, temp, '/'))
			{
				values.push_back(std::stof(temp));
			}
			float x = std::stof(temp);

			muzzle->direction = { values[0], values[1] };
		}
		muzzle->speed = std::stof(rows[3]);
		{
			std::string temp;
			std::stringstream ss(rows[4]);
			std::vector<float> values;
			while (std::getline(ss, temp, '/'))
			{
				values.push_back(std::stof(temp));
			}
			float x = std::stof(temp);

			muzzle->SetPosition({ values[0] + position.x, values[1] + position.y });
		}
		muzzle->delay = std::stof(rows[5]);
		muzzle->quantity = std::stoi(rows[6]);
		muzzle->interval = std::stof(rows[7]);

		muzzle->isEdit = false;
		muzzle->SetPlayer(player);
		muzzle->Init();
		muzzle->Reset();
		muzzle->Play();
	}
}

void Enemy::SetWall(const sf::FloatRect& wall)
{
	this->wall = wall;

	wallTop = wall.top;
	wallBottom = wall.top + wall.height;
	wallLeft = wall.left;
	wallRight = wall.left + wall.width;
}

void Enemy::OnDamage(float damage, sf::Vector2f dir, float knockback)
{
	if (state == Enemy::State::Die) return;

	if (!superarmor) SetPosition(position + dir * knockback);
	SetFlipX(dir.x > 0.f);
	dir = WhereWay(dir);

	hp = std::max(0.f, hp - damage);
	if (IfHit != nullptr)
	{
		IfHit();
	}

	if (hp <= 0.f)
	{
		if (IfDie != nullptr)
		{
			IfDie(dir);
		}
		else
		{
			OnDie(dir);
		}

		state = Enemy::State::Die;
		shadow.setColor(sf::Color::Transparent);
		return;
	}
	
	
	// Animation
	if (state == Enemy::State::Attack || state == Enemy::State::Skill) return;
	else state = Enemy::State::Hit;

	if (dir == way[0])
	{
		animation.Play("HitUp");
	}
	else if (dir == way[1])
	{
		animation.Play("HitLeftUp");
	}
	else if (dir == way[2])
	{
		animation.Play("HitLeft");
	}
	else if (dir == way[3])
	{
		animation.Play("HitLeftDown");
	}
	else if (dir == way[4])
	{
		animation.Play("HitDown");
	}

}

void Enemy::OnBump()
{
	player->OnPlayerHit();
}

void Enemy::OnDie(const sf::Vector2f& look)
{
	// Animation
	if (look == way[0])
	{
		animation.Play("DieUp");
	}
	else if (look == way[1])
	{
		animation.Play("DieLeftUp");
	}
	else if (look == way[2])
	{
		animation.Play("DieLeft");
	}
	else if (look == way[3])
	{
		animation.Play("DieLeftDown");
	}
	else if (look == way[4])
	{
		animation.Play("DieDown");
	}

	// Drop »óÅÂ
	DropItem::Types itemtype = DropItem::Types::None;
	int quantity = 1;
	int chance = 0;

	switch (type)
	{
	case Enemy::EnemyName::None:
		return;
		break;
	case Enemy::EnemyName::BulletKin:
		itemtype = DropItem::Types::Shell1;
		quantity = 1;
		chance = 50;
		break;
	case Enemy::EnemyName::KeyBulletKin:
		return;
		break;
	case Enemy::EnemyName::ShotgunKinRed:
		itemtype = DropItem::Types::Shell1;
		quantity = 1;
		chance = 50;
		break;
	case Enemy::EnemyName::ShotgunKinBlue:
		itemtype = DropItem::Types::Shell1;
		quantity = 1;
		chance = 50;
		break;
	case Enemy::EnemyName::GatlingGull:
		itemtype = DropItem::Types::HegemonyCredit;
		quantity = Utils::RandomRange(1, 6);
		chance = 100;
		break;
	case Enemy::EnemyName::Count:
		return;
		break;
	default:
		break;
	}

	DropsDropItem(itemtype, quantity, chance);
	state = Enemy::State::Die;
}

void Enemy::OneShot(sf::Vector2f dir, float speed, bool isBlink) // pool¹ÝÈ¯ ÇÊ¿ä
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = scene->GetPoolEnemyBullet().Get();
	bullet->Shoot(dir, speed);
	if (weapon != nullptr)	bullet->SetPosition(weapon->GetGunPoint()); // ±èÇýÁØ Ãß°¡
	else bullet->SetPosition(position);
	bullet->SetBullet(isBlink);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);
}

void Enemy::OneShot(sf::Vector2f dir, sf::Vector2f pos, float speed, bool isBlink)
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = scene->GetPoolEnemyBullet().Get();
	bullet->Shoot(dir, speed);
	bullet->SetPosition(pos);
	bullet->SetBullet(isBlink);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);
}

void Enemy::AngleShot(sf::Vector2f dir, float speed, float angle, bool isBlink)
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = scene->GetPoolEnemyBullet().Get();
	dir = Utils::RotateVector(dir, angle);
	bullet->Shoot(dir, speed);
	if(weapon != nullptr) bullet->SetPosition(weapon->GetGunPoint());  // ±èÇýÁØ Ãß°¡
	else bullet->SetPosition(position);
	bullet->SetBullet(isBlink);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);
}

void Enemy::AngleShot(sf::Vector2f dir, sf::Vector2f pos, float speed, float angle, bool isBlink)
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = scene->GetPoolEnemyBullet().Get();
	dir = Utils::RotateVector(dir, angle);
	bullet->Shoot(dir, speed);
	bullet->SetPosition(pos);
	bullet->SetBullet(isBlink);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);
}

void Enemy::ShotgunShot(sf::Vector2f dir, float speed, int quantity, float angle)
{
	float sp = (float)quantity * 0.5f * -angle;
	for (int i = 0; i < quantity; i++)
	{
		AngleShot(dir, speed, sp + angle * i);
	}
}

void Enemy::ShotgunShot(sf::Vector2f dir, sf::Vector2f pos, float speed, int quantity, float angle)
{
	float sp = (float)quantity * 0.5f * -angle;
	for (int i = 0; i < quantity; i++)
	{
		AngleShot(dir, pos, speed, sp + angle * i);
	}
}

void Enemy::Boom(sf::Vector2f pos, float range)
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	
	SpriteEffect* aiming = scene->GetPoolSpriteEffect().Get();
	aiming->SetEffect(SpriteEffect::Effect::Aiming);
	aiming->SetPosition(pos);
	aiming->Init();
	aiming->Reset();
	SpriteEffect* ptr = aiming;
	aiming->action = [this, scene, pos, range, ptr]()
	{
		EnemyBullet* bullet = scene->GetPoolEnemyBullet().Get();
		bullet->Shoot({ 0.f, 0.f }, 500.f);
		bullet->SetPosition(pos);
		bullet->SetBullet(true);
		bullet->SetPlayer(player);
		bullet->Init();
		bullet->Reset();
		bullet->SetScale(range, range);
		scene->AddGo(bullet);

		ptr->action = nullptr;
	};
	scene->AddGo(aiming);
}

void Enemy::CloseAttack(float range)
{
	if (Utils::Distance(player->GetPosition(), position) <= range)
	{
		player->OnPlayerHit();
	}
}

void Enemy::SixWayDie(sf::Vector2f dir, float speed, int chance)
{
	if (int ran = Utils::RandomRange(0, 100) >= chance)
	{
		OnDie(dir);
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		OneShot(Utils::DirectionFromAngle(60.f + 60.f * i), speed, true);
	}

	DropsDropItem(DropItem::Types::Shell1, 1, 50);
	state = Enemy::State::Die;
	SetActive(false);
}

void Enemy::DropsDropItem(DropItem::Types itemtype, int quantity, int chance)
{
	if (int ran = Utils::RandomRange(0, 100) >= chance)
	{
		return;
	}

	for (int i = 0; i < quantity; i++)
	{
		SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
		DropItem* dropitem = scene->GetPoolDropItem().Get();
		dropitem->SetType(itemtype);
		dropitem->SetPlayer(player);
		dropitem->SetPosition(position + Utils::RandomInCircle(100.f));
		dropitem->Init();
		dropitem->Reset();
		scene->AddGo(dropitem);
	}
}
