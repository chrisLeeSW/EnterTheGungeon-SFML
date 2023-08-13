#pragma once
#include "SpriteGo.h"


class Tile : public SpriteGo 
{
protected:
	sf::Vector2i size;
	sf::Vector2f startPos;
	std::string fileName;
	
	
public:
	Tile(const std::string& textureId = "", const std::string& n = "",std::string fileName ="");
	virtual ~Tile() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


	
};

