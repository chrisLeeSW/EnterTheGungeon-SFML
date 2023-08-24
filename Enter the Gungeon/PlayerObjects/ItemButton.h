#pragma once
#include "GameObject.h"

class Book;

class ItemButton : public GameObject
{

public:

	std::string itemname;
	std::string manual;
	std::string itemspriteId;
	std::string textureId;
	std::string fontId;
	sf::Vector2f namepos;
	sf::Vector2f manualpos;
	int textsize;
	int namesize;

	bool isHover = false;
	bool isClickButton = false;
	sf::Vector2f spriteposition;

	sf::Sprite sprite;
	sf::Sprite itemsprite;
	sf::Text manualtext;
	sf::Text nametext;

	Book* book;

public:
	ItemButton(const std::string& n = "");
	virtual ~ItemButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);

	void SetSpritePosition(float x, float y);
	void SetSpritePosition(float x);

	void SetBook(Book* book) { this->book = book; }
	sf::Vector2f GetSpritePosition();
};

