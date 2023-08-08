#pragma once
#include "Scene.h"

class SpriteGo;
class TileMap;

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

	SpriteGo* testPlayerCollied;
	sf::Vector2f playerPos;
	sf::Vector2f playerDir;

	std::vector<sf::RectangleShape> wallColliedShape;
	sf::RectangleShape shape;
public:
	SceneMaptool();
	virtual ~SceneMaptool() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

