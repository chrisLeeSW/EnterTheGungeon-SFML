#pragma once
#include "Scene.h"

class SpriteGo;
class TileMap;
class UiButton;
class TextGo;
class TextBox;
class SpriteGo;
struct TileSpriteInfo
{
	SpriteGo* spr;
	MapObjectType type;
};

class SceneMaptool : public Scene
{
protected:
	TileMap* gridTile =nullptr;
	TileMap* objectSprite = nullptr;
	TileMap* thirdSprite = nullptr;
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

	UiButton* restUi;
	TextGo* restUiText;

	float doubleBySclaeX;
	float doubleBySclaeY;
	
	bool drawGridAllowed = false;
	std::vector<sf::VertexArray> linesMap;

	TextBox* fileNameTexBox;
	std::string fileNameString;

	std::vector<TileSpriteInfo> tiles;
	SpriteGo* currentTileSprite;
	SpriteGo* currentTileSpriteBackGround;


	int fileCount;
	bool IncreaseOrDecrease = false;//
	bool makeGridCheck = false;
	std::vector<std::string> fileList;

	bool increaseWidth;
	bool decreaseWidth;
	bool increaseHeight;
	bool decreaseHeight;


	UiButton* wallButton;
	TextGo* wallButtonText;

	UiButton* wallBlockerButton;
	TextGo* wallBlockerButtonText;

	UiButton* fallingZoneButton;
	TextGo* fallingZoneButtonText;

	UiButton* teleportZoneButton;
	TextGo* teleportZoneButtonText;


	bool setWall;
	bool deleteWall;
	std::vector<WallTypeInfo> colliedShape;
	sf::Vector2f isPrevPos;
	int currentCplliedShapeType;
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

	void MakeLine();
	void RestLine();
	void MakeGrid();
	void ResetGrid();
	void WallMakeCollied();
	void WallResetCollied();

	void AllWallTyepeTextReset();

	void SaveRoom(std::string& fileName, std::string route, std::string saveFileNameCsv);
	void LoadGridAndObjectSpriteFile(std::string& fileName, std::string& route, std::string saveFileNameCsv);


	void ListFilesInDirectory(const std::string & folderPath);

};
