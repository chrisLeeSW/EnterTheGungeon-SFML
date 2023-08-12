#pragma once
#include "SpriteGo.h"
#include "UiButton.h"
#include "Weapon.h"
#include "AnimationController.h"

class TextGo;

class Equipment : public SpriteGo
{

protected:

	AnimationController animation;

	sf::Vector2f windowsize;
	std::unordered_map<UiButton*, std::string> mapweapons;

	std::vector<UiButton*> weaponsUI;

	UiButton* but1;


	bool bookOn = false;

	bool draw;

public:

	Equipment(const std::string& textureId = "", const std::string& n = "");
	virtual ~Equipment() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Insert();
};