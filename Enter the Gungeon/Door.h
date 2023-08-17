#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
class Door :	public SpriteGo
{
public:
	enum class DoorDirectionLook
	{
		Up,
		Left,
		Right,
		Down,
	};
	Door(const std::string& textureId = "", const std::string& n = "");
	virtual ~Door() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void Open();
	void Close();
	void EnterRoom();
	void ExitRoom();

protected:
	AnimationController animation;


};

