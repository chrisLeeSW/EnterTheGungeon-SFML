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
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			//OneShot(dir, speed);
		};
		Pattern3 = [this](sf::Vector2f dir, float speed)
		{
			EndPattern();
		};
		maxHp = 700.f; // table »ç¿ë
		break;
	default:
		std::cerr << "ERROR: Wrong EnemyName (Boss Init())" << std::endl;
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
			break;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::H)) //test
	{
		pattern = PatternNum::None;
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
			Pattern1(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P2:
		if (Pattern2 != nullptr)
		{
			Pattern2(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P3:
		if (Pattern3 != nullptr)
		{
			Pattern3(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P4:
		if (Pattern4 != nullptr)
		{
			Pattern4(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P5:
		if (Pattern5 != nullptr)
		{
			Pattern5(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P6:
		if (Pattern6 != nullptr)
		{
			Pattern6(prevDir, speed);
		}
		else
		{
			EndPattern();
		}
		break;
	case PatternNum::P7:
		if (Pattern7 != nullptr)
		{
			Pattern7(prevDir, speed);
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

void Boss::EndPattern()
{
	pattern = PatternNum::None;
}
