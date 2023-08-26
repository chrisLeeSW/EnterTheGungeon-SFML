#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class SpriteEffect : public SpriteGo
{
public:
	enum class Effect
	{
		None = -1,

		Aiming,

		Count,
	};

protected:
	AnimationController animation;
	SpriteEffect::Effect effect;

public:
	ObjectPool<SpriteEffect>* pool = nullptr;

	SpriteEffect(const std::string& textureId = "", const std::string& n = "");
	virtual ~SpriteEffect() override { };

	void SetEffect(SpriteEffect::Effect effect);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	std::function<void()> action;
};

