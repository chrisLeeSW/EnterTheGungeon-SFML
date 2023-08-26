#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class InteractionObject : public SpriteGo
{
protected:
	bool breakPlayAnimation = false;
	AnimationController animation;
	MapObjectType type;
	
public:
	InteractionObject(MapObjectType type,const std::string& textureId = "", const std::string& n = "");
	virtual ~InteractionObject() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	
	void PlayAnimation(MapObjectType type);
};

