#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Scene.h"
#include "WeaponMgr.h"
#include "ItemMgr.h"
#include "Item.h"
#include "Passive.h"
#include "Active.h"
#include "PlayerUI.h"
#include "DataTableMgr.h"
#include "PlayerTable.h"
#include "Weapon.h"
#include "SceneGame.h"
#include "Book.h"


Player::Player(Types type, const std::string& textureId, const std::string& n) : SpriteGo(textureId, n), type(type)
{
}

void Player::Init()
{

	if (PLAYER_MGR.player != nullptr)
		PLAYER_MGR.player = nullptr;
		PLAYER_MGR.SetPlayer(this);

	


	std::string name;
	std::string rollname;
	windowsize = FRAMEWORK.GetWindowSize();


		switch (type)
		{
		case Types::Pilot :
			name = "Pilot/Pilot";
			rollname = "Pilot/Pilot";
			animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/" + name + "InGungeon.csv"));
			break;
		case Types::Prisoner :
			name = "Prisoner/Prisoner";
			rollname = "Prisoner/Prisoner";
			animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/" + name + "InGungeon.csv"));
			break;
		case Types::WeaponPilot :
			name = "Pilot/PilotWeapon";
			rollname = "Pilot/Pilot";
			animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/" + rollname + "Die.csv"));
			blankBullet.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BlankBullet.csv"));
			blankBullet.SetTarget(&blanksprite);

			blankEffect.setFillColor(sf::Color::Transparent);
			blankEffect.setOutlineColor(sf::Color::White);
			blankEffect.setOutlineThickness(1);
			blankEffect.setOutlineColor(sf::Color(255, 255, 255, 88));
			blankEffect.setRadius(30.f);
			break;
		case Types::WeaponPrisoner : 
			name = "Prisoner/PrisonerWeapon";
			rollname = "Prisoner/Prisoner";
			animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/" + rollname + "Die.csv"));
			blankBullet.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BlankBullet.csv"));
			blankBullet.SetTarget(&blanksprite);

			blankEffect.setFillColor(sf::Color::Transparent);
			blankEffect.setOutlineColor(sf::Color::White);
			blankEffect.setOutlineThickness(1);
			blankEffect.setOutlineColor(sf::Color(255, 255, 255, 88));
			blankEffect.setRadius(30.f);
			break;
		}

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"IdleUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"IdleDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"IdleRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"IdleUpRight.csv"));
																   			
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"WalkUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"WalkUpRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"WalkRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+name+"WalkDown.csv"));
																   			
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+rollname+"RollUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+rollname+"RollDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+rollname+"RollRight.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/"+rollname+"RollUpRight.csv"));
				
		
	actEffect.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/WalkEffect.csv"));

	actEffect.SetTarget(&walk);

	walk.setScale(0.5,0.5);
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

	originalColor = sprite.getColor();
}

void Player::Release()
{
}

void Player::Reset()
{
	SpriteGo::Reset();

	animation.Play("IdleRight");
	SetFlipX(false);
	
	hp = maxHp;
	isAlive = true;


	currentClipInfo = clipInfos[6];

	SetType(type);

	if(isGame)
	{
		GetItem(Active::Types::PrisonerActive);
		GetItem(passivetype);
		GetItem(weapontype);
		playerUI->CurrentWeapon(weaponList[currentIndex]);
		playerUI->CurrentActive(active);
	}
}

void Player::Update(float dt)
{
	if (PLAYER_MGR.IsPause())
		return;

	SetOrigin(Origins::BC);
	animation.Update(dt);

	effect -= dt;

	if (isChangeScene)
	{
		if(animation.GetCurrentClipId() != "InGungeon")
			animation.Play("InGungeon");

		if (animation.AnimationEnd())
		{
			isChangeSceneGame = true;
			//isChangeScene = false;
		}
	}

	if(isAlive && !isChangeScene)
	{
		BlankBullet(dt);

		currenthitDelay -= dt;
		if(currenthitDelay <= 0)
		sprite.setColor(originalColor);

		actEffect.Update(dt);

		if(isHit)
		{
			ouchoriginalColor.a -= 1.f;
			ouch->sprite.setColor(ouchoriginalColor);
			if (ouchoriginalColor.a == 0)
			{
				isHit = false;
			}
		}

		if (iswalk)
		{
			if (iswalk && effect <= 0)
			{
				walk.setScale(0.5, 0.5);
				actEffect.Play("walkEffect");
				walk.setPosition(GetPosition());
				effect = 0.6f;
			}
		}
		else if (!iswalk && actEffect.AnimationEnd())
		{
			walk.setScale(0, 0);
		}

		if (playerchoise || isGame)
		{
			PlayerAct(dt);
			SwapWeapon();
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			{
				if (active != nullptr)
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

		if (!weaponList.empty())
			weaponList[currentIndex]->Update(dt);

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			if (active != nullptr)
				active->isUsingActiveSkill = true;
		}

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
		{
			OnPlayerHit();
			std::cout << hp << std::endl;
		}
	}
	else if(!isAlive && animation.GetCurrentClipId() != "Die")
	{
		animation.Play("Die");
		walk.setScale(0.f,0.f);
		hand.setScale(0.f, 0.f);
	}

}

void Player::Draw(sf::RenderWindow& window)
{

	if (!weaponList.empty() && isAlive)
	weaponList[currentIndex]->Draw(window);

	window.draw(walk);

	if(isBlankAnimation)
	{
		window.draw(blanksprite);
		window.draw(blankEffect);
	}

	SpriteGo::Draw(window);
	if(!isrolling)
	window.draw(hand);
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

void Player::BlankBullet(float dt)
{
	if (blankBulletCount != 0 && INPUT_MGR.GetKeyDown(sf::Keyboard::Q))
	{
		blanksprite.setPosition(sprite.getPosition());
		blankEffect.setPosition(sprite.getPosition());
		blankEffect.setScale(1, 1);
		blankBullet.Play("BlankBullet");
		blankBulletCount--;
		playerUI->UseBlankBullet();
		isBlank = true;
	}

	if (isBlank)
	{
		isBlankEffect = true;
		isBlankAnimation = true;
	}

	if (isBlankAnimation)
	{
		blankBullet.Update(dt);
		blanksprite.setOrigin(blanksprite.getLocalBounds().width * 0.5f, blanksprite.getLocalBounds().height * 0.5f);
		if (blankBullet.AnimationEnd())
			isBlankAnimation = false;

		if (blankEffect.getScale().x >= 15.f)
		{
			isBlank = false;
			isBlankEffect = false;
		}
		if (!isBlankEffect)
		{
			blankEffect.setScale(0, 0);
		}
		else
		{
			blankEffect.setScale(blankEffect.getScale().x + 0.3, blankEffect.getScale().y + 0.3);
			blankEffect.setOrigin(blankEffect.getLocalBounds().width / 2, blankEffect.getLocalBounds().height / 2);

		}
	}
}

void Player::SetFlipX(bool filp)
{
	flipX = filp;

	sf::Vector2f scale1 = sprite.getScale();
	scale1.x = !flipX ? abs(scale1.x) : -abs(scale1.x);
	sprite.setScale(scale1);
	if (isGame)
	{
		playerhand = handPos;
		playerhand.x = !flipX ? abs(handPos.x) : -abs(handPos.x);
	}

}

void Player::PlayerAct(float dt)
{
	prevPlayerPos = position;
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

	if (clipId == currentClipInfo.walk)
	{
		iswalk = true;
	}
	else
		iswalk = false;

	if (isGame && INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
	{
		//GetItem(Passive::Types::PilotPassive);
		GetItem(Weapon::Types::Pad);
		GetItem(Weapon::Types::PrisonerWeapon);
		GetItem(Weapon::Types::ShotGun);
	}

	if (isGame && INPUT_MGR.GetKeyDown(sf::Keyboard::Num8))
		GetItem(Active::Types::PrisonerActive);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F))
	{
		HealHp(10);

		AddBlankBullet();
	}
}


void Player::ChangePlayer(sf::Vector2f pos,bool choise)
{
	SetPosition(pos);
	playerchoise = choise;
}

void Player::SetSceneGame()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Hand.png");



	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	hand.setTexture(*tex);

	Utils::SetOrigin(hand, Origins::MC);
	
	ouch = (SpriteGo*)sceneGame->AddGo(new SpriteGo("graphics/ouch.png"));

	sf::Texture texture;
	texture.loadFromFile("graphics/ouch.png");

	sf::Vector2f originalTextureSize(texture.getSize().x, texture.getSize().y);

	// 원하는 크기로 스케일 조절
	sf::Vector2f desiredSize(windowsize); // 원하는 크기
	ouch->SetScale(desiredSize.x / originalTextureSize.x, desiredSize.y / originalTextureSize.y);
	ouch->SetOrigin(Origins::MC);
	ouch->sortLayer = 101;
	ouch->SetPosition(windowsize * 0.5f);
	ouchoriginalColor = ouch->sprite.getColor();
	ouchoriginalColor.a = 0;
	ouch->sprite.setColor(ouchoriginalColor);

}

void Player::GetItem(Passive::Types type)
{
	if (type == Passive::Types::None)
		return;

	auto it = ITEM_MGR.GetItem(type);

	if (it != nullptr)
	{
		it->Init();
		book->GetItem(it->GetItemType(), it->GetItemWAP());
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
	if (type == Active::Types::None)
		return;

	auto it = ITEM_MGR.GetItem(type);

	if (it != nullptr)
	{
		if (active != nullptr)
			active = nullptr; // 이게 맞나?

		if(playerUI!=nullptr)
		playerUI->CurrentActive(it);

			active = it;
			book->GetItem(it->GetItemType(), it->GetItemWAP());

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
	if (type == Weapon::Types::None)
		return;

	auto it = ITEM_MGR.GetItem(type);
	if (it!=nullptr)
	{
		it->Init();
		book->GetItem(it->GetItemType(), it->GetItemWAP());

		weaponList.push_back(it);
		inventoryweaponList.push_back(type);
	}
	else
	{
		std::cerr << "Not Exist Weapon Item" << std::endl;
	}
}


void Player::HealHp(int heal)
{
	hp = std::min(hp + heal, maxHp);
	playerUI->RenewHp(hp, maxHp);
}

void Player::AddBlankBullet()
{
	blankBulletCount++;
	playerUI->AddBlankBullet();
}

void Player::AddMoney(int money)
{
	this->money += money;
	playerUI->RenewMoney();
}

void Player::AddKey(int key)
{
	this->key += key;
	playerUI->RenewKey();
}


void Player::AddHegemonyCredit(int hegemonyCredit)
{
	Scene::hegemonyCredit += hegemonyCredit;
	book->RenewHegemonyCredit();
}

const sf::Vector2f& Player::GetDirection() const
{
	return direction;
}

void Player::Shoot(Bullet::Types type, sf::Vector2f pos, sf::Vector2f dir, float santan)
{
	bullet = poolBullets.Get();
	bullet->SetBullet(type, pos, dir, santan);

	if (sceneGame != nullptr)
	{
		bullet->SetEnemy(WEAPON_MGR.GetEnemyList());
		sceneGame->AddGo(bullet);
		playerUI->ShootWeapon();
	}
}

void Player::SetEnemyList(std::list<Enemy*> enemylist)
{
	this->enemylist = enemylist;
	WEAPON_MGR.SetEnemyList(enemylist);
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
				playerUI->CurrentWeapon(weaponList[currentIndex]);
				playerUI->SwapWeaponText();
			}
		}
	}
}


void Player::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	if (isGame)
	{
		hand.setPosition(GetPosition() + playerhand);
	}
}

void Player::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	if (isGame)
	{
		hand.setPosition(GetPosition() + playerhand);
	}
}

void Player::OnPlayerHit()
{
	
	if (currenthitDelay <= 0)
	{
		--hp;
		sprite.setColor(sf::Color::Red);
		currenthitDelay = hitDelay;
		ouchoriginalColor.a = MAX_BYTE_VALUE;

		isHit = true;
		playerUI->RenewHp(hp, maxHp);
	}
	if (hp <= 0)
	{
		sprite.setColor(originalColor);
		isAlive = false;
	}
}

void Player::SetType(Types t)
{
	const PlayerInfo* info = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::Player)->Get(t);

	type = info->type;
	activetype = info->activetype;
	passivetype = info->passivetype;
	weapontype = info->weapontype;
	speed = info->speed;
	rollspeed = info->rollspeed;
	maxHp = info->maxHp;
	hp = maxHp;

	hitDelay = info->hitDelay;
	isGame = info->isGame;
	isLobby = info->isLobby;
	blankBulletCount = info->blankBulletCount;


	if(isGame)
	{
		SetSceneGame();
		Scene* scene = SCENE_MGR.GetGameScene();
		sceneGame = dynamic_cast<SceneGame*>(scene);
		ObjectPool<Bullet>* ptr = &poolBullets;
		poolBullets.OnCreate = [ptr](Bullet* bullet) {
			bullet->pool = ptr;
		};
		poolBullets.Init();
		book = PLAYER_MGR.GetBook();

	}
}

void Player::SetBook(Book* book)
{
	this->book = book;
}