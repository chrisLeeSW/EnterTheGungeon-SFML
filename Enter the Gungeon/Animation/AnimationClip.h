#pragma once

enum class AnimationLoopTypes
{
	Single, // 한번 동작
	Loop,  // 계속 동작 시키기
};
struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;  
	// int형의 Rect만들어서 top left width height 로 값을만듬
	std::function<void()> action;
};

struct AnimationClip 
//매 프레임을 가지고 있는 Clip
{
	std::string id;
	AnimationLoopTypes loopType;
	int fps;

	std::vector<AnimationFrame> frames;
	bool LoadFromFile(const std::string path);
};