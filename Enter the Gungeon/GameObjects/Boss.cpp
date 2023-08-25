#include "stdafx.h"
#include "Boss.h"

Boss::Boss(EnemyName type, const std::string& textureId, const std::string& n)
	:Enemy(type, textureId, n)
{
	
}

Boss::~Boss()
{
	Release();
}

void Boss::Init()
{
	std::string name;
	switch (type)
	{
	case EnemyName::GatlingGull:
		name = "GatlingGull/GatlingGull";
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/GatlingGull/GatlingGullPattern6-1.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/GatlingGull/GatlingGullPattern6-2.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/GatlingGull/GatlingGullPattern7.csv"));

		IfHit = [this]()
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
			scene->RenewBossUI();
		};
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			state = Enemy::State::Skill;
			CloseAttack(200.f);
		};
		Pattern1 = [this](sf::Vector2f dir, float speed)
		{
			if (patternCount < 30)
			{
				patternDuration = 0.1f;
				AngleShot(dir, position + GatlingGullMuzzlePos(), 200.f, Utils::RandomRange(-30.f, 30.f));
				patternCount++;
			}
			else
			{
				patternDuration = 1.0f;
				patternCount = 0;
				EndPattern();
			}
		};
		Pattern2 = [this](sf::Vector2f dir, float speed)
		{
			if (patternCount < 30)
			{
				patternDuration = 0.1f;
				int value = patternCount % 10;
				if (value > 4)
				{
					value = 10 - value;
				}
				AngleShot(dir, position + GatlingGullMuzzlePos(), 200, -20.f + 10.f * value);
				patternCount++;
			}
			else
			{
				patternDuration = 1.0f;
				patternCount = 0;
				EndPattern();
			}
		};
		Pattern3 = [this](sf::Vector2f dir, float speed)
		{
			EndPattern();
		};
		Pattern4 = [this](sf::Vector2f dir, float speed)
		{
			state = Enemy::State::Bind;

			if (patternCount < 2)
			{
				ShotgunShot(dir, position + GatlingGullMuzzlePos(), 200, 10, 10.f);
				patternCount++;
			}
			else
			{
				patternCount = 0;
				EndPattern();
			}

		};
		Pattern5 = [this](sf::Vector2f dir, float speed)
		{
			EndPattern(); return; //test

			state = Enemy::State::Bind;

			if (animation.AnimationEnd())
			{
				LoadMuzzle("bulletPattern/Circle.csv");
				EndPattern();
			}
		};
		Pattern6 = [this](sf::Vector2f dir, float speed)
		{
			EndPattern(); return; //test

			state = Enemy::State::Bind;
			if (animation.GetCurrentClipId() != "Pattern6-1")
			{
				animation.Play("Pattern6-1");
			}

			if (animation.AnimationEnd())
			{
				state = Enemy::State::Skill;
				animation.Play("Pattern6-2");
				SetPosition(player->GetPosition());
				EndPattern(false);
			}
		};
		Pattern7 = [this](sf::Vector2f dir, float speed)
		{
			EndPattern(); return; //test

			state = Enemy::State::Bind;

			if (animation.AnimationEnd())
			{
				animation.Play("Pattern7");
			}

			if (patternCount < 12)
			{
				patternDuration = 0.5f;
				Boom(player->GetPosition() + Utils::RandomInCircle(250.f), 4.f);
				patternCount++;
			}
			else
			{
				patternDuration = 1.0f;
				patternCount = 0;
				EndPattern();
			}
		};
		patternDuration = 1.0f;
		break;
	default:
		std::cerr << "ERROR: Wrong BossName (Boss Init())" << std::endl;
		break;
	}
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "IdleUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "IdleLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "IdleLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "IdleLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "IdleDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "MoveUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "MoveLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "MoveLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "MoveLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "MoveDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "AttackUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "AttackLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "AttackLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "AttackLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "AttackDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "HitUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "HitLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "HitLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "HitLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "HitDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "DieUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "DieLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "DieLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "DieLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/" + name + "DieDown.csv"));

	animation.SetTarget(&sprite);
}

void Boss::Reset()
{
	Enemy::Reset();

	patternTimer = 0.f;
}

void Boss::Update(float dt)
{
	if (PLAYER_MGR.IsPause())
		return;

	Enemy::Update(dt);
	
	patternTimer += dt;
	if (patternTimer >= patternDuration)
	{
		patternTimer = 0.f;
		
		switch (pattern)
		{
		case PatternNum::None:
			pattern = (PatternNum)Utils::RandomRange(1, (int)PatternNum::Count);
			break;
		default:
			PlayPattern(pattern);
			break;
		}
	}
}

void Boss::SetBoss(float patternDuration)
{
	this->patternDuration = patternDuration;
}

void Boss::PlayPattern(const PatternNum& p)
{
	switch (p)
	{
	case PatternNum::P1:
		if (Pattern1 != nullptr)
		{
			Pattern1(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P2:
		if (Pattern2 != nullptr)
		{
			Pattern2(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P3:
		if (Pattern3 != nullptr)
		{
			Pattern3(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P4:
		if (Pattern4 != nullptr)
		{
			Pattern4(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P5:
		if (Pattern5 != nullptr)
		{
			Pattern5(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P6:
		if (Pattern6 != nullptr)
		{
			Pattern6(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P7:
		if (Pattern7 != nullptr)
		{
			Pattern7(direction, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	default:
		break;
	}
}

void Boss::EndPattern(bool idle)
{
	if (idle) state = Enemy::State::Idle;
	pattern = PatternNum::None;
}

const Enemy::EnemyName& Boss::GetType() const
{
	return type;
}

sf::Vector2f Boss::GatlingGullMuzzlePos()
{
	sf::Vector2f pos = WhereWay(direction);
	
	if (pos == way[0])
	{
		pos.x = -12.f;
		pos.y = -60.f;
	}
	else if (pos == way[1])
	{
		pos.x = -22.f;
		pos.y = -48.f;
	}
	else if (pos == way[2])
	{
		pos.x = -30.f;
		pos.y = -25.f;
	}
	else if (pos == way[3])
	{
		pos.x = -24.f;
		pos.y = 0.f;
	}
	else if (pos == way[4])
	{
		pos.x = -10.f;
		pos.y = 0.f;
	}
	if (flipX) pos.x = -pos.x;

	return pos;
}

