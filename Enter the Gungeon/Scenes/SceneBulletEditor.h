#pragma once
#include "Scene.h"

class Muzzle;
class TextBox;

class SceneBulletEditor : public Scene
{
protected:
	Muzzle* curMuzzle = nullptr;
	std::list<Muzzle*> muzzlelist;

	TextBox* directionTB;
	TextBox* speedTB;
	TextBox* positionTB;
	TextBox* delayTB;
	TextBox* quantityTB;
	TextBox* intervalTB;
	TextBox* filepathTB;

public:
	SceneBulletEditor();
	virtual ~SceneBulletEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Apply();
	bool ValidFilePath(const std::string& filepath); //파일 경로 유효성 검사
	void SaveCSV(const std::string& filepath);
	void OverwriteCSV(const std::string& filepath);
	void LoadCSV(const std::string& filepath);
};