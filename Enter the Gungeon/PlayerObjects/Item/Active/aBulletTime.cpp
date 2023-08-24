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
	textbut->text.setCharacterSize(50);
	textbut->text.setFillColor(sf::Color::White);
	textbut->SetOrigin(Origins::TL);
	textbut->text.setString("Bullet Time");
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
		textbut->SetPosition(0,0);

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
