#pragma once
#include "Scene.h"

class SpriteGo;
class TileMap;
class UiButton;
class TextGo;

struct TileSpriteInfo
{
	SpriteGo* spr;
	MapObjectType type;
};
class SceneMaptool : public Scene
{
protected:
	TileMap* gridTile =nullptr;
	float view;

	UiButton* wallWidthSprite;
	UiButton* wallWidthCountIncrease;
	UiButton* wallWidthCountDecrease;
	TextGo* wallWidthCountText;
	TextGo* wallWidthCountIncreaseText;
	TextGo* wallWidthCountDecreaseText;
	int wallWidthCount;
	int minWallWidthCount;

	UiButton* wallHeightSprite;
	UiButton* wallHeightCountIncrease;
	UiButton* wallHeightCountDecrease;
	TextGo* wallHeightCountText;
	TextGo* wallHeightCountIncreaseText;
	TextGo* wallHeightCountDecreaseText;
	int wallHeightCount;
	int minWallHeightCount;

	UiButton* saveUi;
	TextGo* saveUiText;

	UiButton* loadUi;
	TextGo* loadUiText;
	
	UiButton* makeUi;
	TextGo* makeUiText;

	float doubleBySclaeX;
	float doubleBySclaeY;
	
	bool drawGridAllowed = false;
	std::vector<sf::VertexArray> linesMap;

	
	std::vector<TileSpriteInfo> tiles;
	SpriteGo* currentTileSprite;
	SpriteGo* currentTileSpriteBackGround;

	bool setTile;
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
	void SettingTileSprite(const std::string& path);

};
