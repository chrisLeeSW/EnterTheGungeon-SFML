#include "stdafx.h"
#include "ItemButton.h"
#include "SceneMgr.h"

ItemButton::ItemButton(const std::string& n)
	:GameObject(n)
{
}

ItemButton::~ItemButton()
{
}

void ItemButton::Init()
{
	sf::Font* font = RESOURCE_MGR.GetFont(fontId);
	if (font != nullptr)
	{
		manualtext.setFont(*font);
		nametext.setFont(*font);
	}

	manualtext.setCharacterSize(textsize);
	manualtext.setString(manual);
	manualtext.setPosition(manualpos);
	manualtext.setFillColor(sf::Color::White);

	nametext.setCharacterSize(namesize);
	nametext.setString(itemname);
	nametext.setPosition(namepos);
	nametext.setFillColor(sf::Color::Black);

	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		sprite.setTexture(*tex);
	}
	Utils::SetOrigin(sprite, Origins::MC);

	tex = RESOURCE_MGR.GetTexture(itemspriteId);
	if (tex != nullptr)
	{
		itemsprite.setTexture(*tex);
	}
	itemsprite.setPosition(375,120);

	Utils::SetOrigin(nametext,Origins::MC);
	Utils::SetOrigin(manualtext, Origins::MC);
	Utils::SetOrigin(itemsprite, Origins::MC);



	isHover = false;

	std::cout << "������ ��ư ����" << std::endl;
	std::cout << "��Ʈ ���̵� : " << fontId << std::endl;
	std::cout << "�ؽ��� ���̵� : " << textureId << std::endl;
	std::cout << "������ ��������Ʈ ���̵� : " << itemspriteId << std::endl;
}

void ItemButton::Release()
{
	
}

void ItemButton::Reset()
{

}

void ItemButton::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
	
	
	std::cout << "���콺 X ������ :" << uiMousePos.x << "\n"<<"���콺 Y ������ : " << uiMousePos.y << std::endl;


	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	if (!prevHover && isHover)
	{
		if (OnEnter != nullptr)
			OnEnter();
	}
	if (prevHover && !isHover)
	{
		if (OnExit != nullptr)
			OnExit();
	}
	if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		book->SetCurrentClickButton(this);
		isClickButton = true;
		if (OnClick != nullptr)
			OnClick();
	}
}

void ItemButton::Draw(sf::RenderWindow& window)
{
	//std::cout << "������ ��ư ��ο�" << std::endl;

		window.draw(itemsprite);
		window.draw(manualtext);
		window.draw(nametext);

}

void ItemButton::SetPosition(const sf::Vector2f& p)
{
	manualtext.setPosition(p);
	nametext.setPosition(p);
}

void ItemButton::SetPosition(float x, float y)
{

	manualtext.setPosition(x,y);
	nametext.setPosition(x,y);
}

void ItemButton::SetOrigin(Origins origin)
{
	Utils::SetOrigin(manualtext, origin);
	Utils::SetOrigin(nametext, origin);
}

void ItemButton::SetSpritePosition(float x, float y)
{
	spriteposition = sf::Vector2f({ x,y });
	sprite.setPosition(spriteposition);
}

void ItemButton::SetSpritePosition(float x)
{
	spriteposition.x -= x;
	sprite.setPosition(spriteposition);
}


sf::Vector2f ItemButton::GetSpritePosition()
{
	return spriteposition;
}
