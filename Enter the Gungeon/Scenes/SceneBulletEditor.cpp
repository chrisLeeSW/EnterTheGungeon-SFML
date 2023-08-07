#include "stdafx.h"
#include "SceneBulletEditor.h"
#include "Bullet.h"
#include "UiButton.h"

SceneBulletEditor::SceneBulletEditor() : Scene(SceneId::BulletEditor)
{
	resourceListPath = "script/SceneBulletEditorResourceList.csv";
}

void SceneBulletEditor::Init()
{
	Release();

	Bullet* test1 = (Bullet*)AddGo(new Bullet(BulletType::EnemyBullet));
	test1->SetScale(3.0f, 3.0f);
	test1->SetBullet(false);

	Bullet* test2 = (Bullet*)AddGo(new Bullet(BulletType::EnemyBullet));
	test2->SetScale(3.0f, 3.0f);
	test2->SetBullet(true);

	UiButton* test3 = (UiButton*)AddGo(new UiButton("graphics/testbutton.png", "fonts/DIGITALDREAM.ttf", "test3"));
	test3->text.setCharacterSize(20);
	test3->text.setString("1234");
	test3->text.setFillColor(sf::Color::Black);
	test3->SetOrigin(Origins::MR);
	test3->SetPosition(windowSize.x, 100.0f);
	test3->sortLayer = 100;
	test3->OnClick = [this]()
	{
		str = InputString();
		UiButton* test3 = (UiButton*)FindGo("test3");
		test3->text.setString(str);
		test3->Reset();
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

    return inputString;
}