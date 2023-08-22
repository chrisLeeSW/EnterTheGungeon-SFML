#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
class Door : public SpriteGo
{
public:
	enum class DoorDirectionLook
	{
		None = -1,
		Up,
		Down,
		Left,
		Right
	};
	Door(int type,const std::string& textureId = "", const std::string& n = "");
	virtual ~Door()= default;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void Open();
	void Close();
	void EnterRoom();
	void ExitRoom();

protected:
	AnimationController animation;
	DoorDirectionLook type;
	bool open;

};

