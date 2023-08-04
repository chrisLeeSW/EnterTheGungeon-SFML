#include "stdafx.h"
#include "ResourceMgr.h"
#include "rapidcsv.h"
ResourceMgr::~ResourceMgr()
{
	for (auto pair : mapTexture)
	{
		delete std::get<0>(pair.second);
	}
	mapTexture.clear();
	for (auto pair : mapFont)
	{
		delete std::get<0>(pair.second);
	}
	mapFont.clear();
	for (auto pair : mapSoundBuffer)
	{
		delete std::get<0>(pair.second);
	}
	mapSoundBuffer.clear();
}

void ResourceMgr::Init()
{
	LoadCSVFILE("script/DefaultResourceList.csv");
}

void ResourceMgr::UnLoadAll()
{
	auto itMapTexture = mapTexture.begin();
	while (itMapTexture != mapTexture.end())
	{
		if (!std::get<1>(itMapTexture->second))
		{
			delete std::get<0>(itMapTexture->second);
			itMapTexture = mapTexture.erase(itMapTexture);
		}
		else
		{
			itMapTexture++;
		}
	}
	auto itMapFont = mapFont.begin();
	while (itMapFont != mapFont.end())
	{
		if (!std::get<1>(itMapFont->second))
		{
			delete std::get<0>(itMapFont->second);
			itMapFont = mapFont.erase(itMapFont);
		}
		else
		{
			itMapFont++;
		}
	}
	auto itMapSoundBuffer = mapSoundBuffer.begin();
	while (itMapSoundBuffer != mapSoundBuffer.end())
	{
		if (!std::get<1>(itMapSoundBuffer->second))
		{
			delete std::get<0>(itMapSoundBuffer->second);
			itMapSoundBuffer = mapSoundBuffer.erase(itMapSoundBuffer);
		}
		else
		{
			itMapSoundBuffer++;
		}
	}

	auto itMapAnimationClip = mapAnimationClip.begin();
	while (itMapAnimationClip != mapAnimationClip.end())
	{
		if (!std::get<1>(itMapAnimationClip->second))
		{
			delete std::get<0>(itMapAnimationClip->second);
			itMapAnimationClip = mapAnimationClip.erase(itMapAnimationClip);
		}
		else
		{
			itMapAnimationClip++;
		}
	}
}

void ResourceMgr::LoadCSVFILE(const std::string path)
{
	rapidcsv::Document doc(path); 
	std::vector<int> types = doc.GetColumn<int>(0);
	std::vector<std::string> paths = doc.GetColumn<std::string>(1);
	for (int i = 0;i < types.size();++i)
	{
		Load((ResourceTypes)types[i], paths[i]);
	}
}

void ResourceMgr::Load(ResourceTypes t, const std::string path, bool isDefault)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		if (mapTexture.end() == it)
		{
			auto texture = new sf::Texture();
			texture->loadFromFile(path);
			mapTexture.insert({ path, {texture,isDefault } });
		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (mapFont.end() == it)
		{
			auto font = new sf::Font();
			font->loadFromFile(path);
			mapFont.insert({ path, {font,isDefault} });
		}
	}
	break;
	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(path);
		if (mapSoundBuffer.end() == it)
		{
			auto sb = new sf::SoundBuffer();
			sb->loadFromFile(path);
			mapSoundBuffer.insert({ path, {sb,isDefault} });
		}
	}
	break;
	case ResourceTypes::AimationClip:
	{
		auto it = mapAnimationClip.find(path);
		if (mapAnimationClip.end() == it)
		{
			auto clip = new AnimationClip();
			bool check = clip->LoadFromFile(path);
			mapAnimationClip.insert({ path,{clip,isDefault} });
		}
	}
	break;
	}


}

void ResourceMgr::Unload(ResourceTypes t, const std::string id)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(id);
		if (it != mapTexture.end())
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				mapTexture.erase(it);
			}
			else
			{
				std::cout << "ERR : Default Resource" << std::endl;
			}

		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(id);
		if (it != mapFont.end())
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				mapFont.erase(it);
			}
			else
			{
				std::cout << "ERR : Default Resource" << std::endl;
			}
		}
	}
	break;
	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(id);
		if (it != mapSoundBuffer.end())
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				mapSoundBuffer.erase(it);
			}
			else
			{
				std::cout << "ERR : Default Resource" << std::endl;
			}
		}
	}
	break;
	case ResourceTypes::AimationClip:
	{
		auto it = mapAnimationClip.find(id);
		if (it != mapAnimationClip.end())
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				mapAnimationClip.erase(it);
			}
			else
			{
				std::cout << "ERR : Default Resource" << std::endl;
			}
		}
	}
	break;
	}
}
//
//void ResourceMgr::Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
//{
//	for (const auto& tuple : array)
//	{
//		Unload(std::get<0>(tuple), std::get<1>(tuple));
//	}
//}

sf::Texture* ResourceMgr::GetTexture(const std::string& id)
{
	auto it = mapTexture.find(id);
	if (it != mapTexture.end())
	{
		return  std::get<0>(it->second);
	}
	return nullptr;
}

sf::Font* ResourceMgr::GetFont(const std::string& id)
{
	auto it = mapFont.find(id);
	if (it != mapFont.end())
	{
		return  std::get<0>(it->second);
	}
	return nullptr;
}

sf::SoundBuffer* ResourceMgr::GetSoundBuffer(const std::string& id)
{
	auto it = mapSoundBuffer.find(id);
	if (it != mapSoundBuffer.end())
	{
		return  std::get<0>(it->second);
	}
	return nullptr;
}

AnimationClip* ResourceMgr::GetAnimationClip(const std::string& id)
{
	auto it = mapAnimationClip.find(id);
	if (it != mapAnimationClip.end())
	{
		return  std::get<0>(it->second);
	}
	return nullptr;
}
