#include "stdafx.h"
#include "aBulletTime.h"
#include "ItemMgr.h"
#include "TextGo.h"
#include "Scene.h"
#include "SceneGame.h"

aBulletTime::aBulletTime(const std::string& textureId, const std::string& n) : Active(textureId,n)
{

}

void aBulletTime::Init()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	textbut = (TextGo*)sceneGame->AddGo(new TextGo("fonts/AurulentSansMono-Regular.otf", "textbut"));
	textbut->sortLayer = 103;
	textbut->text.setCharacterSize(300);
	textbut->text.setFillColor(sf::Color::Magenta);
	textbut->SetPosition(FRAMEWORK.GetWindowSize()/2.f);
	textbut->SetOrigin(Origins::MC);
	textbut->text.setString("The World");
	textbut->SetActive(false);
}

void aBulletTime::Release()
{
}

void aBulletTime::Reset()
{
}

void aBulletTime::Update(float dt)
{
	if (isUsingActiveSkill)
	{
		textbut->SetPosition(FRAMEWORK.GetWindowSize() * Utils::RandomValue());

		textbut->SetActive(true);
		ITEM_MGR.BulletTimeOn(isbullettime);
		duration -= dt;

		if (duration <= 0)
		{
			isbullettime = false;
			textbut->SetActive(false);
			ITEM_MGR.BulletTimeOn(isbullettime);
			isUsingActiveSkill = false;
		}
	}
}

void aBulletTime::Draw(sf::RenderWindow& window)
{
}
