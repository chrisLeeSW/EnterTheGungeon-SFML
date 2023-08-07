#pragma once
#include "Scene.h"

class SpriteGo;

enum class MapObjectType
{
	None = -1,
	Wall,
	Tile,
	wallObjectUp,
	WallObjectDown,
};
struct TextureInfo
{
	sf::IntRect textureRect;
	int sortLayer;
	int sortOrder;
};
class SceneMaptool : public Scene
{
protected:
	std::vector<MapObjectType> mapObjectTypes;

	std::string mapSpriteId="";

	std::vector<TextureInfo> textureInfo;

	std::vector<sf::IntRect> textureRectSzie;
	std::vector<int> mapSortLayer;
	std::vector<int> mapSortOrder;

	std::vector<SpriteGo*> mapInfo;

	int maxRowCount;
public:
	SceneMaptool();
	virtual ~SceneMaptool() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void LoadFromMapObjectTypeFile(std::string path);
	void LoadFromMapFile(std::string path);
	void SettingRoom();
};

