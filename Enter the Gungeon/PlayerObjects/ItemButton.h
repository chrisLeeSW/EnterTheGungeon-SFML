#pragma once
#include "SpriteGo.h"

class ItemButton : public SpriteGo
{

public:

	std::string itemname;
	std::string manual;
	std::string itemsprite;
	sf::Vector2f namepos;
	sf::Vector2f manualpos;

	bool isHover = false;
	std::string fontId;

public:
	ItemButton(const std::string& textureId = "", const std::string& fontId = "", const std::string& n = "");
	virtual ~ItemButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);

	sf::Text text;
	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;
};

