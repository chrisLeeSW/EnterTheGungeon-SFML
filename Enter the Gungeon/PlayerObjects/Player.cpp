#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Scene.h"
#include "WeaponMgr.h"
#include "ItemMgr.h"
#include "Item.h"
#include "Passive.h"
#include "Active.h"


Player::Player(Types type, const std::string& textureId, const std::string& n) : SpriteGo(textureId, n), type(type)
{
}


void Player::Init()
{
	windowsize = FRAMEWORK.GetWindowSize();

	if (PLAYER_MGR.player != nullptr)
		PLAYER_MGR.player = nullptr;
		PLAYER_MGR.SetPlayer(this);


	switch (type)
	{
	case Types::Pilot:
	{
		//파일럿 기본 애니메이션
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
		break;
	}
	case Types::WeaponPilot:
	{
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponIdleUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponIdleDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponIdleRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponIdleUpRight.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponWalkUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponWalkUpRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponWalkRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotWeaponWalkDown.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotRollUpRight.csv"));
		//WEAPON_MGR.Enter(Weapon::Types::PilotWeapon);
		break;
	}
	case Types::Prisoner:
	{
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerIdleUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerIdleDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerIdleRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerIdleUpRight.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerWalkUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerWalkUpRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerWalkRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerWalkDown.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerRollUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerRollDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerRollRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PrisonerRollUpRight.csv"));
		std::cout << "죄수 타입" << std::endl;
		break;
	}
	case Types::WeaponPrisoner:
	{

		break;
	}

	default:
	{
		std::cout << "노 타입" << std::endl;
		break;
	}
	}


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

		if (type == Types::WeaponPilot || type == Types::WeaponPrisoner)
		{
			playerchoise = true;
			SetSceneGame();
			GetItem(Passive::Types::PilotPassive);
			GetItem(Active::Types::PrisonerActive);
			GetItem(Weapon::Types::Magnum);
		}
}

void Player::Release()
{
}

void Player::Reset()
{
	SpriteGo::Reset();
	animation.Play("IdleRight");
	//SetPosition(windowsize.x * 0.5, windowsize.y * 0.5);
	SetFlipX(false);

	if (type == Types::WeaponPilot || type == Types::WeaponPrisoner)
	{
		hand->SetOrigin(-sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height * 0.4);
		active->Init();
		passiveList.back()->Init();
	}

	speed = 150.f;
	rollspeed = 250.f;
	currentClipInfo = clipInfos[6];


}

void Player::Update(float dt)
{
	SetOrigin(Origins::BC);
	animation.Update(dt);

	if(!weaponList.empty())
	weaponList[currentIndex]->Update(dt);

	if (playerchoise)
	{
		PlayerAct(dt);
		SwapWeapon();
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			active->Update(dt);
		}
	}
	else
	{
		if (animation.GetCurrentClipId() != "IdleRight")
		{
			animation.Play("IdleRight");
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		active->isUsingActiveSkill = true;
	}
}

void Player::Draw(sf::RenderWindow& window)
{

	if (!weaponList.empty())
	weaponList[currentIndex]->Draw(window);

	SpriteGo::Draw(window);
}

void Player::PlayerRotation()
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	angle = Utils::Angle2(look);


	//스위치로 묶을 것 (인트로 변환해서)
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


	sf::Vector2f scale1 = sprite.getScale();
	scale1.x = !flipX ? abs(scale1.x) : -abs(scale1.x);
	sprite.setScale(scale1);
	if (hand != nullptr)
	{
		sf::Vector2f scale2 = hand->sprite.getScale();
		scale2.x = !flipX ? abs(scale2.x) : -abs(scale2.x);
		hand->sprite.setScale(scale2);
	}

	//if(WEAPON_MGR.GetWithWeapon())
	//WEAPON_MGR.SetWeaPonFlipx(filp);
}

void Player::PlayerAct(float dt)
{

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
			if ((animation.AnimationEnd()))
			{
				isrolling = false;
			}
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

	if (INPUT_MGR.GetKey(sf::Keyboard::Num9))
	{
		GetItem(Passive::Types::PilotPassive);
		GetItem(Active::Types::PrisonerActive);
		GetItem(Weapon::Types::PilotWeapon);
	}
}


void Player::ChangePlayer(sf::Vector2f pos,bool choise)
{
	SetPosition(pos);
	playerchoise = choise;
}

void Player::SetSceneGame()
{
	isGame = true;
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	hand = (SpriteGo*)sceneGame->AddGo(new SpriteGo("graphics/Hand.png"));
}

void Player::GetItem(Passive::Types type)
{
	auto it = ITEM_MGR.GetItem(type);

	if (it != nullptr)
	{
		it->Init();
		passiveList.push_back(it);
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		sceneGame->AddGo(passiveList.back());

	}
	else
	{
		std::cout << "Not Exist Passive Item" << std::endl;
	}
}

void Player::GetItem(Active::Types type)
{
	auto it = ITEM_MGR.GetItem(type);

	if (it != nullptr)
	{
		if (active != nullptr)
			active = nullptr; // 이게 맞나?

			active = it;
			Scene* scene = SCENE_MGR.GetCurrScene();
			SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
			sceneGame->AddGo(active);
			active->Init();
	}
	else
	{
		std::cout << "Not Exist Active Item" << std::endl;
	}
}

void Player::GetItem(Weapon::Types type)
{
	auto it = ITEM_MGR.GetItem(type);
	if (it!=nullptr)
	{
		it->Init();
		weaponList.push_back(it);
	}
	else
	{
		std::cerr << "Not Exist Weapon Item" << std::endl;
	}
}

void Player::SwapWeapon()
{
	for (const auto& pair : keyToIndexMap)
	{
		if (INPUT_MGR.GetKeyDown(pair.first))
		{
			if(pair.second <= weaponList.size())
			{
				int temp = pair.second;
				--temp;
				currentIndex = temp;
			}
		}
	}
}


void Player::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	if (hand != nullptr)
		hand->SetPosition(p);
}

void Player::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	if (hand != nullptr)
		hand->SetPosition(x, y);
}

