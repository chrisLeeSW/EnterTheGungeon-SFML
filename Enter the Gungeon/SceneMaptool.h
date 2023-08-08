#pragma once
#include "Scene.h"

class SpriteGo;
class TileMap;
class UiButton;
class TextGo;
struct TextureInfo
{
	sf::IntRect textureRect;
	int sortLayer;
	int sortOrder;
};
class SceneMaptool : public Scene
{
protected:
	TileMap* tileMap;
	float view;

	UiButton* makeWallWidthSprite;
	UiButton* makeWallWidthCountIncrease;
	UiButton* makeWallWidthCountDecrease;
	TextGo* makerWallWidthCountText;
	TextGo* makeWallWidthCountIncreaseText;
	TextGo* makeWallWidthCountDecreaseText;
	int makeWallWidthCount;
	int minWallWidthCount;

	UiButton* makeWallHeightSprite;
	UiButton* makeWallHeightCountIncrease;
	UiButton* makeWallHeightCountDecrease;
	TextGo* makerWallHeightCountText;
	TextGo* makeWallHeightCountIncreaseText;
	TextGo* makeWallHeightCountDecreaseText;
	int makeWallHeightCount;
	int minWallHeightCount;

	UiButton* saveUi;
	TextGo* saveUiText;

	UiButton* loadUi;
	TextGo* loadUiText;
	
	UiButton* makeUi;
	TextGo* makeUiText;

	float doubleBySclaeX;
	float doubleBySclaeY;
	
	bool drawShape = false;
	std::vector<sf::RectangleShape> shape;
	std::vector<sf::VertexArray> lines;
public:
	SceneMaptool();
	virtual ~SceneMaptool() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SettingUiSprite();
	void SettingUiText();
};



/*SpriteGo* testPlayerCollied;
sf::Vector2f playerPos;
sf::Vector2f playerDir;

std::vector<sf::RectangleShape> wallColliedShape;
sf::RectangleShape shape;*/