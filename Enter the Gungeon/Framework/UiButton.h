#pragma once
#include "SpriteGo.h"
class UiButton : public SpriteGo
{
protected:
	bool isHover = false;
	std::string fontId;
public:
	UiButton(const std::string& textureId="", const std::string& fontId="", const std::string& n = "");
	virtual ~UiButton() override;

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

// Ui 버튼 쓸수 있는 Class 만듬