#include "stdafx.h"
#include "SceneBulletEditor.h"
#include "Muzzle.h"
#include "UiButton.h"
#include "TextBox.h"

SceneBulletEditor::SceneBulletEditor() : Scene(SceneId::BulletEditor)
{
	resourceListPath = "script/SceneBulletEditorResourceList.csv";
}

void SceneBulletEditor::Init()
{
	Release();

	worldView.setSize(windowSize * 0.5f);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	UiButton* blinkbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/AurulentSansMono-Regular.otf", "blinkbutton"));
	blinkbutton->text.setCharacterSize(20);
	blinkbutton->text.setString("false");
	blinkbutton->text.setFillColor(sf::Color::Black);
	blinkbutton->SetOrigin(Origins::MC);
	blinkbutton->SetPosition(windowSize.x - 150.f, 50.f);
	blinkbutton->sortLayer = 100;
	blinkbutton->OnClick = [this]()
	{
		if (curMuzzle == nullptr) return;

		curMuzzle->isBlink = !curMuzzle->isBlink;

		UiButton* blinkbutton = (UiButton*)FindGo("blinkbutton");
		blinkbutton->text.setString((curMuzzle->isBlink) ? "true" : "false");
		blinkbutton->Reset();
	};

	directionTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "direction"));
	directionTB->box.setSize({200, 50});
	directionTB->text.setCharacterSize(10);
	directionTB->SetOrigin(Origins::MC);
	directionTB->SetPosition(windowSize.x - 150.f, 100.f);
	directionTB->sortLayer = 100;

	speedTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "speed"));
	speedTB->box.setSize({200, 50});
	speedTB->text.setCharacterSize(10);
	speedTB->SetOrigin(Origins::MC);
	speedTB->SetPosition(windowSize.x - 150.f, 150.f);
	speedTB->sortLayer = 100;

	positionTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "position"));
	positionTB->box.setSize({ 200, 50 });
	positionTB->text.setCharacterSize(10);
	positionTB->SetOrigin(Origins::MC);
	positionTB->SetPosition(windowSize.x - 150.f, 200.f);
	positionTB->sortLayer = 100;

	delayTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "delay"));
	delayTB->box.setSize({ 200, 50 });
	delayTB->text.setCharacterSize(10);
	delayTB->SetOrigin(Origins::MC);
	delayTB->SetPosition(windowSize.x - 150.f, 250.f);
	delayTB->sortLayer = 100;

	quantityTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "quantity"));
	quantityTB->box.setSize({ 200, 50 });
	quantityTB->text.setCharacterSize(10);
	quantityTB->SetOrigin(Origins::MC);
	quantityTB->SetPosition(windowSize.x - 150.f, 300.f);
	quantityTB->sortLayer = 100;

	intervalTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "interval"));
	intervalTB->box.setSize({ 200, 50 });
	intervalTB->text.setCharacterSize(10);
	intervalTB->SetOrigin(Origins::MC);
	intervalTB->SetPosition(windowSize.x - 150.f, 350.f);
	intervalTB->sortLayer = 100;

	UiButton* newbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/AurulentSansMono-Regular.otf", "newbutton"));
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

		muzzlelist.push_back(muzzle);
	};

	filepathTB = (TextBox*)AddGo(new TextBox("fonts/AurulentSansMono-Regular.otf", "filepath"));
	filepathTB->box.setSize({ 200, 50 });
	filepathTB->text.setCharacterSize(10);
	filepathTB->SetOrigin(Origins::MC);
	filepathTB->SetPosition(150.f, 150.f);
	filepathTB->sortLayer = 100;

	UiButton* savebutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/AurulentSansMono-Regular.otf", "playbutton"));
	savebutton->text.setCharacterSize(20);
	savebutton->text.setString("SAVE");
	savebutton->text.setFillColor(sf::Color::Black);
	savebutton->SetOrigin(Origins::MC);
	savebutton->SetPosition(150.f, 250.f);
	savebutton->sortLayer = 100;
	savebutton->OnClick = [this]()
	{
		rapidcsv::Document doc(filepathTB->text.getString(), rapidcsv::LabelParams(-1, -1));

	};
	UiButton* loadbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/AurulentSansMono-Regular.otf", "playbutton"));
	loadbutton->text.setCharacterSize(20);
	loadbutton->text.setString("LOAD");
	loadbutton->text.setFillColor(sf::Color::Black);
	loadbutton->SetOrigin(Origins::MC);
	loadbutton->SetPosition(150.f, 300.f);
	loadbutton->sortLayer = 100;
	loadbutton->OnClick = [this]()
	{
		rapidcsv::Document doc(filepathTB->text.getString(), rapidcsv::LabelParams(-1, -1));

	};

	UiButton* playbutton = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/AurulentSansMono-Regular.otf", "playbutton"));
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

				directionTB->text.setString(std::to_string(curMuzzle->direction.x) + "/" + std::to_string(curMuzzle->direction.y));
				directionTB->Reset();

				speedTB->text.setString(std::to_string(curMuzzle->speed));
				speedTB->Reset();

				positionTB->text.setString(std::to_string(curMuzzle->GetPosition().x) + '/' + std::to_string(curMuzzle->GetPosition().y));
				positionTB->Reset();

				delayTB->text.setString(std::to_string(curMuzzle->delay));
				delayTB->Reset();

				quantityTB->text.setString(std::to_string(curMuzzle->quantity));
				quantityTB->Reset();

				intervalTB->text.setString(std::to_string(curMuzzle->interval));
				intervalTB->Reset();

				break;
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		Apply();
	}
}

void SceneBulletEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneBulletEditor::Apply()
{
	if (muzzlelist.empty()) return;
	
	// direction Apply
	{
		std::string temp;
		std::stringstream ss(directionTB->text.getString());
		std::vector<float> values;
		while (std::getline(ss, temp, '/'))
		{
			values.push_back(std::stof(temp));
		}
		float x = std::stof(temp);

		curMuzzle->direction = { values[0], values[1] };
	}
	
	// speed Apply
	{
		std::string str = speedTB->text.getString();

		curMuzzle->speed = std::stof(str);
	}

	// position Apply
	{
		std::string temp;
		std::stringstream ss(positionTB->text.getString());
		std::vector<float> values;
		while (std::getline(ss, temp, '/'))
		{
			values.push_back(std::stof(temp));
		}
		float x = std::stof(temp);

		curMuzzle->SetPosition({ values[0], values[1] });
	}

	// delay Apply
	{
		std::string str = delayTB->text.getString();

		curMuzzle->delay = std::stoi(str);
	}

	// quantity Apply
	{
		std::string str = quantityTB->text.getString();

		curMuzzle->quantity = std::stoi(str);
	}

	// interval Apply
	{
		std::string str = intervalTB->text.getString();

		curMuzzle->interval = std::stof(str);
	}
}