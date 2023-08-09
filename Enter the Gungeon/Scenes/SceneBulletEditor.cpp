#include "stdafx.h"
#include "SceneBulletEditor.h"
#include "EnemyBullet.h"
#include "UiButton.h"
#include "TextGo.h"

SceneBulletEditor::SceneBulletEditor() : Scene(SceneId::BulletEditor)
{
	resourceListPath = "script/SceneBulletEditorResourceList.csv";
}

void SceneBulletEditor::Init()
{
	Release();

	EnemyBullet* test1 = (EnemyBullet*)AddGo(new EnemyBullet(BulletType::EnemyBullet));
	test1->SetScale(3.0f, 3.0f);
	test1->Init();
	bulletlist.push_back(test1);
	curBullet = test1;

	UiButton* blinkbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "blinkbutton"));
	blinkbutton->text.setCharacterSize(20);
	blinkbutton->text.setString("false");
	blinkbutton->text.setFillColor(sf::Color::Black);
	blinkbutton->SetOrigin(Origins::MC);
	blinkbutton->SetPosition(windowSize.x - 150.f, 50.f);
	blinkbutton->sortLayer = 100;
	blinkbutton->OnClick = [this]()
	{
		curBullet->SetBullet(!curBullet->IsBlink());
		curBullet->Reset();

		UiButton* blinkbutton = (UiButton*)FindGo("blinkbutton");
		blinkbutton->text.setString((curBullet->IsBlink()) ? "true" : "false");
		blinkbutton->Reset();
	};

	UiButton* directionbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "directionbutton"));
	directionbutton->text.setCharacterSize(10);
	directionbutton->text.setString("x,y,speed,range");
	directionbutton->text.setFillColor(sf::Color::Black);
	directionbutton->SetOrigin(Origins::MC);
	directionbutton->SetPosition(windowSize.x - 150.f, 100.f);
	directionbutton->sortLayer = 100;
	directionbutton->OnClick = [this]()
	{
		str = InputString();
		UiButton* directionbutton = (UiButton*)FindGo("directionbutton");
		directionbutton->text.setString(str);
		directionbutton->Reset();

		std::string temp;
		std::stringstream ss(str);
		std::vector<float> values;
		while (std::getline(ss, temp, '/'))
		{
			values.push_back(std::stof(temp));
		}
		float x = std::stof(temp);

		curBullet->Shoot({ values[0], values[1] }, values[2], values[3]);
	};

	UiButton* positionbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "positionbutton"));
	positionbutton->text.setCharacterSize(10);
	positionbutton->text.setString("position");
	positionbutton->text.setFillColor(sf::Color::Black);
	positionbutton->SetOrigin(Origins::MC);
	positionbutton->SetPosition(windowSize.x - 150.f, 150.f);
	positionbutton->sortLayer = 100;
	positionbutton->OnClick = [this]()
	{
		str = InputString();
		UiButton* positionbutton = (UiButton*)FindGo("positionbutton");
		positionbutton->text.setString(str);
		positionbutton->Reset();

		std::string temp;
		std::stringstream ss(str);
		std::vector<float> values;
		while (std::getline(ss, temp, '/'))
		{
			values.push_back(std::stof(temp));
		}
		float x = std::stof(temp);

		curBullet->SetPosition({ values[0], values[1] });
	};

	UiButton* newbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "newbutton"));
	newbutton->text.setCharacterSize(20);
	newbutton->text.setString("new bullet");
	newbutton->text.setFillColor(sf::Color::Black);
	newbutton->SetOrigin(Origins::MC);
	newbutton->SetPosition(150.f, 50.f);
	newbutton->sortLayer = 100;
	newbutton->OnClick = [this]()
	{
		EnemyBullet* bullet = (EnemyBullet*)AddGo(new EnemyBullet(BulletType::EnemyBullet));
		bullet->SetScale(3.0f, 3.0f);
		bullet->SetPosition(0.f, 0.f);
		bullet->Init();
		bullet->Reset();

		bulletlist.push_back(bullet);
	};

	UiButton* playbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "playbutton"));
	playbutton->text.setCharacterSize(20);
	playbutton->text.setString("PLAY");
	playbutton->text.setFillColor(sf::Color::Black);
	playbutton->SetOrigin(Origins::MC);
	playbutton->SetPosition(150.f, 900.f);
	playbutton->sortLayer = 100;
	playbutton->OnClick = [this]()
	{
		isPlay = !isPlay;
		UiButton* playbutton = (UiButton*)FindGo("playbutton");
		(isPlay) ? playbutton->text.setString("PAUSE") : playbutton->text.setString("PLAY");
		playbutton->Reset();
	};

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneBulletEditor::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneBulletEditor::Enter()
{
	Scene::Enter();

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


}

void SceneBulletEditor::Exit()
{
	Scene::Exit();
}

void SceneBulletEditor::Update(float dt)
{
	Scene::Update(dt);

	if (!isPlay)
	{
		for (auto it : bulletlist)
		{
			it->Update(-dt);
		}
	}

	if (INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{
		if (curBullet == nullptr) return;

		for (auto it : bulletlist)
		{
			if (it->sprite.getGlobalBounds().contains(ScreenToWorldPos(INPUT_MGR.GetMousePos())))
			{
				curBullet = it;

				UiButton* blinkbutton = (UiButton*)FindGo("blinkbutton");
				blinkbutton->text.setString((curBullet->IsBlink()) ? "true" : "false");
				blinkbutton->Reset();

				UiButton* directionbutton = (UiButton*)FindGo("directionbutton");
				directionbutton->text.setString("x,y,speed,range");
				directionbutton->Reset();

				UiButton* positionbutton = (UiButton*)FindGo("positionbutton");
				positionbutton->text.setString(std::to_string(curBullet->GetPosition().x) + '/' + std::to_string(curBullet->GetPosition().y));
				positionbutton->Reset();
			}
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneBulletEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

std::string SceneBulletEditor::InputString()
{
    std::string inputString;
    bool done = false;

    while (!done)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    inputString += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == '\b' && !inputString.empty())
                {
                    inputString.pop_back();
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    done = true;
                }
            }
        }
        window.display();
    }
	inputString.pop_back();

    return inputString;
}