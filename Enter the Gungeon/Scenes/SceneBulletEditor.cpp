#include "stdafx.h"
#include "SceneBulletEditor.h"
#include "Muzzle.h"
#include "UiButton.h"

SceneBulletEditor::SceneBulletEditor() : Scene(SceneId::BulletEditor)
{
	resourceListPath = "script/SceneBulletEditorResourceList.csv";
}

void SceneBulletEditor::Init()
{
	Release();

	UiButton* blinkbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "blinkbutton"));
	blinkbutton->text.setCharacterSize(20);
	blinkbutton->text.setString("false");
	blinkbutton->text.setFillColor(sf::Color::Black);
	blinkbutton->SetOrigin(Origins::MC);
	blinkbutton->SetPosition(windowSize.x - 150.f, 50.f);
	blinkbutton->sortLayer = 100;
	blinkbutton->OnClick = [this]()
	{
		curMuzzle->isBlink = !curMuzzle->isBlink;

		UiButton* blinkbutton = (UiButton*)FindGo("blinkbutton");
		blinkbutton->text.setString((curMuzzle->isBlink) ? "true" : "false");
		blinkbutton->Reset();
	};

	UiButton* directionbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "directionbutton"));
	directionbutton->text.setCharacterSize(10);
	directionbutton->text.setString("direction");
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

		curMuzzle->direction = { values[0], values[1] };
	};

	UiButton* speedbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "speedbutton"));
	speedbutton->text.setCharacterSize(10);
	speedbutton->text.setString("speed");
	speedbutton->text.setFillColor(sf::Color::Black);
	speedbutton->SetOrigin(Origins::MC);
	speedbutton->SetPosition(windowSize.x - 150.f, 150.f);
	speedbutton->sortLayer = 100;
	speedbutton->OnClick = [this]()
	{
		str = InputString();
		UiButton* speedbutton = (UiButton*)FindGo("speedbutton");
		speedbutton->text.setString(str);
		speedbutton->Reset();

		curMuzzle->speed = std::stof(str);
	};

	UiButton* positionbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "positionbutton"));
	positionbutton->text.setCharacterSize(10);
	positionbutton->text.setString("position");
	positionbutton->text.setFillColor(sf::Color::Black);
	positionbutton->SetOrigin(Origins::MC);
	positionbutton->SetPosition(windowSize.x - 150.f, 200.f);
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

		curMuzzle->SetPosition({ values[0], values[1] });
	};

	UiButton* quantitybutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "quantitybutton"));
	quantitybutton->text.setCharacterSize(10);
	quantitybutton->text.setString("quantity");
	quantitybutton->text.setFillColor(sf::Color::Black);
	quantitybutton->SetOrigin(Origins::MC);
	quantitybutton->SetPosition(windowSize.x - 150.f, 250.f);
	quantitybutton->sortLayer = 100;
	quantitybutton->OnClick = [this]()
	{
		str = InputString();
		UiButton* quantitybutton = (UiButton*)FindGo("quantitybutton");
		quantitybutton->text.setString(str);
		quantitybutton->Reset();

		curMuzzle->quantity = std::stoi(str);
	};

	UiButton* intervalbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "intervalbutton"));
	intervalbutton->text.setCharacterSize(10);
	intervalbutton->text.setString("interval");
	intervalbutton->text.setFillColor(sf::Color::Black);
	intervalbutton->SetOrigin(Origins::MC);
	intervalbutton->SetPosition(windowSize.x - 150.f, 300.f);
	intervalbutton->sortLayer = 100;
	intervalbutton->OnClick = [this]()
	{
		str = InputString();
		UiButton* intervalbutton = (UiButton*)FindGo("intervalbutton");
		intervalbutton->text.setString(str);
		intervalbutton->Reset();

		curMuzzle->interval = std::stof(str);
	};

	UiButton* newbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "newbutton"));
	newbutton->text.setCharacterSize(20);
	newbutton->text.setString("new muzzle");
	newbutton->text.setFillColor(sf::Color::Black);
	newbutton->SetOrigin(Origins::MC);
	newbutton->SetPosition(150.f, 50.f);
	newbutton->sortLayer = 100;
	newbutton->OnClick = [this]()
	{
		Muzzle* muzzle = (Muzzle*)AddGo(new Muzzle());
		muzzle->Init();
		muzzle->Reset();

		curMuzzle = muzzle;
		muzzlelist.push_back(muzzle);
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
		for (auto it : muzzlelist)
		{
			it->Play();
		}
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

	if (INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{
		for (auto it : muzzlelist)
		{
			if (it->circle.getGlobalBounds().contains(ScreenToWorldPos(INPUT_MGR.GetMousePos())))
			{
				if (curMuzzle != nullptr) curMuzzle->circle.setFillColor(sf::Color::White);
				curMuzzle = it;
				curMuzzle->circle.setFillColor(sf::Color::Red);

				UiButton* blinkbutton = (UiButton*)FindGo("blinkbutton");
				blinkbutton->text.setString((curMuzzle->isBlink) ? "true" : "false");
				blinkbutton->Reset();

				UiButton* directionbutton = (UiButton*)FindGo("directionbutton");
				directionbutton->text.setString(std::to_string(curMuzzle->direction.x) + "/" + std::to_string(curMuzzle->direction.y));
				directionbutton->Reset();

				UiButton* positionbutton = (UiButton*)FindGo("positionbutton");
				positionbutton->text.setString(std::to_string(curMuzzle->GetPosition().x) + '/' + std::to_string(curMuzzle->GetPosition().y));
				positionbutton->Reset();

				UiButton* speedbutton = (UiButton*)FindGo("speedbutton");
				speedbutton->text.setString(std::to_string(curMuzzle->speed));
				speedbutton->Reset();

				UiButton* quantitybutton = (UiButton*)FindGo("quantitybutton");
				quantitybutton->text.setString(std::to_string(curMuzzle->quantity));
				quantitybutton->Reset();

				UiButton* intervalbutton = (UiButton*)FindGo("intervalbutton");
				intervalbutton->text.setString(std::to_string(curMuzzle->interval));
				intervalbutton->Reset();
			}
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Delete))
	{
		muzzlelist.remove(curMuzzle);
		RemoveGo(curMuzzle);
		curMuzzle = nullptr;
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
    }
	inputString.pop_back();

    return inputString;
}