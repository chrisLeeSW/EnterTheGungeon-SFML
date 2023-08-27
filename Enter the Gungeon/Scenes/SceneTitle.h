#pragma once
#include "Scene.h"
#include "AnimationController.h"

class SceneTitle :public Scene
{
protected:
	
	AnimationController animation;

	sf::Sprite sprite;

	sf::Text play;
	sf::Text maptool;
	sf::Text bulletEditor;
	sf::Text language;
	sf::Text close;

	//std::vector<int> selectedTextIndex;

	int selectedTextIndex = 0;


	sf::Color transparentColor;
	sf::Color originalColor;

public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


};
