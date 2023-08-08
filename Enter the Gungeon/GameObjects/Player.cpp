#include "stdafx.h"
#include "Player.h"


Player::Player(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
	
}

void Player::Init()
{
	windowsize = FRAMEWORK.GetWindowSize();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotIdleUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotIdleDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotIdleRight.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotIdleUpRight.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWalkUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWalkUpRight.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWalkRight.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWalkDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollRight.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollUpRight.csv"));


	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);


	clipInfos.push_back({ "IdleUpRight", "WalkUpRight","RollUpRight",true, Utils::Normalize({-1.f, -1.f}) });
	clipInfos.push_back({ "IdleUp", "WalkUp","RollUp" ,true, {0.f, -1.f} });
	clipInfos.push_back({ "IdleUpRight", "WalkUpRight", "RollUpRight",false, Utils::Normalize({1.f, -1.f}) });

	clipInfos.push_back({ "IdleRight", "WalkRight","RollRight",true, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleRight", "WalkRight","RollRight",false, {1.f, 0.f} });

	clipInfos.push_back({ "IdleRight", "WalkRight","RollRight", true,Utils::Normalize({-1.f, 1.f}) });
	clipInfos.push_back({ "IdleDown", "WalkDown","RollDown",true,{0.f, 1.f} });
	clipInfos.push_back({ "IdleRight", "WalkRight","RollRight",false, Utils::Normalize({1.f, 1.f}) });

	//무기매니저만들어서 플레이어 컨테이너에서 생성해서 꺼내서 쓰게
}

void Player::Release()
{

}

void Player::Reset()
{
	SpriteGo::Reset();
	animation.Play("IdleUp");
	SetPosition(windowsize.x * 0.5, windowsize.y * 0.5);
	SetFlipX(false);

	sprite.setScale(5, 5);
	speed = 300.f;
	rollspeed = 600.f;
	currentClipInfo = clipInfos[6];

}

void Player::Update(float dt)
{
	SetOrigin(Origins::BC);
	animation.Update(dt);


	if (!isrolling)
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
		magnitude = Utils::Magnitude(direction);
		if (magnitude > 1.f)
		{
			direction /= magnitude;
		}
		position += direction * speed * dt;
		SetPosition(position);
		PlayerRotation();
		clipId = magnitude == 0.f ? currentClipInfo.idle : currentClipInfo.walk;
	}
	else
	{
		position += direction * rollspeed * dt;
		SetPosition(position);
	}


	if (clipId == currentClipInfo.walk && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs) {
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction); });

		isrolling = true;
		currentClipInfo = *min;
		clipId = currentClipInfo.roll;
		if (currentClipInfo.flipX)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
		if (isrolling && animation.GetCurrentClipId() != clipId)
		{
			animation.Play(currentClipInfo.roll);
		}
	}
	else if (animation.GetCurrentClipId() != clipId)
	{

		animation.Play(clipId);
	}

	if (isrolling)
	{
		if ((animation.GetTotalFrame() - animation.GetCurFrame()) == 1)
		{
			isrolling = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::PlayerRotation()
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	angle = Utils::Angle2(look);


	if (angle <= 45.f)
	{
		currentClipInfo = clipInfos[3];
		//오른쪽
	}
	else if (angle <= 135.f)
	{
		currentClipInfo = clipInfos[6];
		//아래
	}
	else if (angle <= 210.f)
	{
		currentClipInfo = clipInfos[3];
		//왼쪽
	}
	else if (angle <= 235.f)
	{
		currentClipInfo = clipInfos[0];
		//왼쪽 위
	}
	else if (angle <= 310.f)
	{
		currentClipInfo = clipInfos[1];
		//위
	}
	else if (angle <= 335.f)
	{
		currentClipInfo = clipInfos[0];
		//오른쪽 위
	}
	else if (angle <= 360.f)
	{
		currentClipInfo = clipInfos[3];
		//오른쪽
	}
	if (angle >= 110.f && angle <= 250.f)
	{
		SetFlipX(true);
	}
	else if(angle <= 70.f || angle >=290.f )
	{
		SetFlipX(false);
	}
}

void Player::SetFlipX(bool filp)
{
	flipX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

sf::Vector2f Player::GetPlayerPos()
{
	return position;
}

