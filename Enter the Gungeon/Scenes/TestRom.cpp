#include "stdafx.h"
#include "TestRom.h"
#include "Room.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "InteractionObject.h"


TestRom::TestRom() :Scene(SceneId::TestRoom)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void TestRom::Init()
{


	rooms = new Room();
	shape.setSize({ 50.f, 50.f });
	ListFilesInDirectory("Room/TileMapFile/");
	int count = 0;
	int rnadFileNumber = 0;
	while (count != rooms->GetRoom().size())
	{
		bool collied = false;
		rnadFileNumber = Utils::RandomRange(0, fileList.size());
		TileMap* map = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		sf::Vector2f pos = { rooms->Center(rooms->GetRoomIndex(count)) };
		map->SetStartPos(pos);

		sf::Vector2f tileMapSize = map->TileMapSize(fileList[rnadFileNumber]);
		sf::Vector2f objpos = pos;
		objpos -= tileMapSize * 0.5f;
		objpos += map->GetTileSize() * 0.5f;



		if (rooms->GetRoomIndex(count).width < tileMapSize.x ||
			rooms->GetRoomIndex(count).height < tileMapSize.y)
		{
			continue;
		}
		map->Load(fileList[rnadFileNumber]);
		map->SetOrigin(Origins::MC);
		std::vector<SpriteGo*> objects;
		std::vector<RoomObjectsInfoTest1> interaction;
		for (int i = 0; i < map->tiles.size(); ++i)
		{
			//	objects
			switch (static_cast<MapObjectType>(map->tiles[i].objectTypes))
			{
			case MapObjectType::WallDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,250,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::LibraryDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,650,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::Pot:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,800,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Book1:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,850,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			}
		}
		tileRoom.push_back({ map, objects, interaction });
		count++;
	}
	connected.resize(tileRoom.size(), false);
	connected[0] = true;
	int currentRoom = 0;
	int lineCount = 0;
	int prevRooom=0;
	while (true)
	{
		int closestRoom = -1;
		float minDistance = std::numeric_limits<float>::max();
		for (size_t i = 1; i < tileRoom.size(); ++i)
		{
			if (!connected[i])
			{
				float dist = Utils::Distance(tileRoom[currentRoom].map->GetStartPos(), tileRoom[i].map->GetStartPos());
				if (dist < minDistance)
				{
					minDistance = dist;
					closestRoom = i;
				}
			}
		}
		if (closestRoom == -1)
		{
			break;
		}
		ConnectRooms(tileRoom[currentRoom].map, tileRoom[closestRoom].map);
		connected[closestRoom] = true;
		prevRooom = currentRoom;
		currentRoom = closestRoom;
	}
	/*{
		sf::Vector2f end = passages[passages.size() - 1].to;
		sf::Vector2f start = passages[passages.size() - 1].from;
		int end1X = end.x * 100;
		int end1Y = end.y * 100;
		int startX = start.x * 100;
		int startY = start.y * 100;
		if ((end1X != startX) || (startX != startY))
		{
			if (end.x > start.x)
			{
				end.x -= tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f + tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
			}
			if (end.x < start.x)
			{
				end.x += tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f - tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
			}
			if (end.y > start.y)
			{
				end.y -= tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5f - tileRoom[currentRoom].map->GetTileSize().y * 0.5f;
			}
			if (end.y < start.y)
			{
				end.y += tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5f - tileRoom[currentRoom].map->GetTileSize().y * 0.5f;
			}
			positions.push_back(end);
		}
	
	}*/

	for (int i = 0; i < tileRoom.size(); ++i)
	{
		for (int k = 0; k < passages.size(); ++k)
		{
			sf::Vector2f pos;
			if (isIntersecting(tileRoom[i].map->vertexArray.getBounds(), passages[k].from, passages[k].to, pos))
			{
				bool isNotPos = false;
				/*for (auto& pushPos : positions)
				{
					if (pushPos == pos)
					{
						isNotPos = true;
						break;
					}
				}*/
				if (!isNotPos)
				{
					sf::Vector2f center = tileRoom[i].map->GetStartPos();
					if (pos.x > center.x)
					{
						pos.x -= tileRoom[i].map->GetTileSize().x * 0.5f;
					}
					if (pos.x < center.x)
					{
						pos.x += tileRoom[i].map->GetTileSize().x * 0.5f;
					}
					if (pos.y > center.y)
					{
						pos.y -= tileRoom[i].map->GetTileSize().y * 0.5f;
					}
					if (pos.y < center.y)
					{
						pos.y += tileRoom[i].map->GetTileSize().y * 0.5f;
					}
					positions.push_back(pos);
				}
			}
		}
	}

	for (int i = 0; i < positions.size(); ++i)
	{
		sf::RectangleShape shpae;
		shpae.setSize({ 25.f,25.f });
		shpae.setPosition(positions[i]);
		Utils::SetOrigin(shpae, Origins::MC);
		doorShape.push_back(shpae);
	}




	std::cout << positions.size() << std::endl;
	for (int i = 0; i < positions.size(); ++i)
	{
		std::cout << i << "번째의 포지션 값 :" << positions[i].x << "\t" << positions[i].y << std::endl;
	}

	std::cout << passages.size() << std::endl;
	for (int i = 0; i < passages.size(); ++i)
	{
		std::cout << i << "번째의 from 값 :" << passages[i].from.x << "\t" << passages[i].from.y << std::endl;
		std::cout << i << "번째의 to 값 :" << passages[i].to.x << "\t" << passages[i].to.y << std::endl;
	}

	int a = 0;
	//for (int i = 1; i < doorShape.size(); ++i)
	//{
	//	while (a != passages.size())
	//	{
	//		sf::Vector2f pos;
	//		if (a == 0)
	//		{
	//			if (isIntersecting(doorShape[i].getGlobalBounds(), positions[i - 1], passages[a].to, pos))
	//			{
	//				CreateTunnel(positions[i - 1], passages[a].to);
	//				a++;
	//				break;
	//			}
	//			else
	//			{
	//				CreateTunnel(positions[i - 1], passages[a].to);
	//				a++;
	//			}
	//		}
	//		else
	//		{
	//			//if (a % 2 == 1)
	//			{
	//				if (isIntersecting(doorShape[i].getGlobalBounds(), passages[a].from, passages[a].to, pos))
	//				{
	//					CreateTunnel(passages[a].from, positions[i - 1]);
	//					a++;
	//					break;
	//				}
	//				else if (isIntersecting(doorShape[i].getGlobalBounds(), positions[i - 1], passages[a].to, pos))
	//				{
	//					CreateTunnel(positions[i - 1], passages[a].to);
	//					a++;
	//					break;
	//				}
	//				else
	//				{
	//					CreateTunnel(positions[i - 1], passages[a].to);
	//					a++;
	//				}
	//			}
	//		}
	//	}
	//}

	/*for (int i = 0; i < passages.size(); ++i)
	{
		CreateTunnel(passages[i].from, passages[i].to);
	}*/

	
	/*for (int i = 0; i < passages.size(); ++i)
	{
		if (i % 2 == 0)
		{
			CreateTunnel(positions[i], passages[i].to);
		}
		else
		{
			CreateTunnel(passages[i].from, positions[i]);
		}
	}*/

	/*int testCount = 0;
	for (int i = 0; i < positions.size(); i+=2)
	{
		for (; testCount < passages.size(); testCount++)
		{
			if (testCount == 0)
			{
				sf::Vector2f pos;
				if (isIntersecting(doorShape[i + 1].getGlobalBounds(), positions[i], passages[testCount].to, pos))
				{
					testCount+=2;
					CreateTunnel(positions[i], pos);
					break;
				}
				else	CreateTunnel(positions[i], passages[testCount].to);
			}
			else if (testCount % 2 == 1)
			{

				CreateTunnel(passages[testCount].from, positions[i+1]);
				testCount++;
				break;
			}
			else if (testCount % 2 == 0 && testCount != 0)
			{
				sf::Vector2f pos;
				if (isIntersecting(doorShape[i + 1].getGlobalBounds(), positions[i], passages[testCount].to, pos))
				{
					testCount+=2;
					CreateTunnel(positions[i], pos);
					break;
				}
				else CreateTunnel(positions[i], passages[testCount].to);
			}
		}
	}*/

	/*	for (int k = 0; k < passages.size(); ++k)
		{
			sf::Vector2f pos;
			if (k == 0)
			{
				if (isIntersecting(doorShape[i].getGlobalBounds(), positions[i - 1], passages[k].to, pos))
				{
					CreateTunnel(positions[i - 1], passages[k].to);
					break;
				}
				else CreateTunnel(positions[i - 1], passages[k].to);
			}
			else
			{
				if (k % 2 == 1)
				{
					if (isIntersecting(doorShape[i].getGlobalBounds(), passages[k].from, passages[k].to, pos))
					{
						CreateTunnel(passages[k].from, passages[k].to);
						break;
					}
				}
				else
				{
					if (isIntersecting(doorShape[i].getGlobalBounds(), passages[k].from, passages[k].to, pos))
					{
						CreateTunnel(passages[k].from, passages[k].to);
						break;
					}
				}
			}
		}*/


	for (auto go : gameObjects)
	{
		go->Init();
	}

}

void TestRom::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	if (rooms != nullptr)
	{
		delete rooms;
		rooms = nullptr;
	}
}

void TestRom::Enter()
{
	Scene::Enter();
	shape.setPosition(tileRoom[0].map->GetStartPos());
	worldView.setSize(windowSize);
	worldView.setCenter(shape.getPosition());

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


}

void TestRom::Exit()
{
	Scene::Exit();
}

void TestRom::Update(float dt)
{
	Scene::Update(dt);
	MoveWorldView();
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		shape.move(5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		shape.move(-5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		shape.move(0.0f, -5.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		shape.move(0.0f, 5.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Add))
	{
		length++;
		test = true;
	}
}

void TestRom::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	//rooms->Draw(window);
	window.draw(shape);
	for (int i = 0; i < length; ++i)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = passages[i].from;
		line[1].position = passages[i].to;
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		window.draw(line);
	}


	/*for (const auto& passage : passages) {
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = passage.from;
		line[1].position = passage.to;
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		window.draw(line);
	}*/


	for (const auto& rect : tunnel)
	{
		window.draw(rect);
	}
	for (const auto& rect : doorShape)
	{
		window.draw(rect);
	}
}

void TestRom::MoveWorldView()
{
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(-5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -5.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 5.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(0.5f);
	}
}

void TestRom::ListFilesInDirectory(const std::string& folderPath)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((folderPath + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "Error finding files in directory." << std::endl;
		return;
	}

	int fileCount = 0;

	do {
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			//std::cout << "파일 이름: " << findFileData.cFileName << std::endl;
			std::string filePath = folderPath + findFileData.cFileName;
			fileList.push_back(filePath);
			++fileCount;
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);

}

sf::Vector2f TestRom::Center(TileMap* room)
{
	return { room->vertexArray.getBounds().width / 2 , room->vertexArray.getBounds().height / 2 };
}

void TestRom::ConnectRooms(TileMap* r1, TileMap* r2)
{
	sf::Vector2f c1 = r1->GetStartPos();
	sf::Vector2f c2 = r2->GetStartPos();
	passages.push_back({ c1, {c2.x, c1.y} });
	passages.push_back({ {c2.x, c1.y}, c2 });

	
	//for (int k = 0; k < passages.size(); ++k)
	//{
	//	sf::Vector2f pos;
	//	if (isIntersecting(r1->vertexArray.getBounds(), passages[k].from, passages[k].to, pos) /*|| isIntersecting(r2->vertexArray.getBounds(), passages[k].from, passages[k].to, pos)*/)
	//	{
	//		bool isNotPos = false;
	//		for (auto& pushPos : positions)
	//		{
	//			if (pushPos == pos)
	//			{
	//				isNotPos = true;
	//				break;
	//			}
	//		}
	//		if (!isNotPos)
	//		{
	//			sf::Vector2f center = r1->GetStartPos();
	//			if (pos.x > center.x)
	//			{
	//				pos.x -= r1->GetTileSize().x * 0.5f;
	//			}
	//			if (pos.x < center.x)
	//			{
	//				pos.x += r1->GetTileSize().x * 0.5f;
	//			}
	//			if (pos.y > center.y)
	//			{
	//				pos.y -=r1->GetTileSize().y * 0.5f;
	//			}
	//			if (pos.y < center.y)
	//			{
	//				pos.y += r1->GetTileSize().y * 0.5f;
	//			}
	//			positions.push_back(pos);
	//		}
	//	}
	//}
	//CreateTunnel(c1, { c2.x, c1.y });
	//CreateTunnel({ c2.x, c1.y }, c2);


}

void TestRom::CreateTunnel(sf::Vector2f start, sf::Vector2f end)
{

	// 터널의 사이즈를 설정합니다.
	const sf::Vector2f tunnelSize(23.f, 23.f);
	const float tunnelSpacing = 5.0f; // 터널 사각형들 간의 간격입니다.
	sf::Vector2f midpoint(start.x, end.y);

	// 시작점에서 중간점까지의 통로를 생성합니다.
	sf::Vector2f direction1 = (midpoint - start) / Utils::Distance(start, midpoint);
	float totalTunnelLength1 = Utils::Distance(start, midpoint);
	int tunnelCount1 = static_cast<int>(totalTunnelLength1 / (tunnelSize.x ));
	for (int i = 0; i < tunnelCount1; ++i)
	{
		sf::RectangleShape tunnelShape;
		tunnelShape.setSize(tunnelSize);
		tunnelShape.setPosition(start + sf::Vector2f{ direction1.x * i, direction1.y * i }*(tunnelSize.x));
		tunnelShape.setRotation(std::atan2(direction1.y, direction1.x) * 180.0f / 3.14159265f);
		tunnelShape.setFillColor(sf::Color::Transparent);
		tunnelShape.setOutlineThickness(2);
		tunnelShape.setOutlineColor(sf::Color::Red);
		Utils::SetOrigin(tunnelShape, Origins::MC);
		tunnel.push_back(tunnelShape);
	}
	// 중간점에서 끝점까지의 통로를 생성합니다.
	sf::Vector2f direction2 = (end - midpoint) / Utils::Distance(midpoint, end);
	float totalTunnelLength2 = Utils::Distance(midpoint, end);
	int tunnelCount2 = static_cast<int>(totalTunnelLength2 / (tunnelSize.x ));
	for (int i = 0; i < tunnelCount2; ++i)
	{
		sf::RectangleShape tunnelShape;
		tunnelShape.setSize(tunnelSize);
		tunnelShape.setPosition(midpoint + sf::Vector2f{ direction2.x * i ,direction2.y * i } *(tunnelSize.x));
		tunnelShape.setRotation(std::atan2(direction2.y, direction2.x) * 180.0f / 3.14159265f);
		tunnelShape.setFillColor(sf::Color::Transparent);
		tunnelShape.setOutlineThickness(1);
		tunnelShape.setOutlineColor(sf::Color::Green);
		Utils::SetOrigin(tunnelShape, Origins::MC);
		tunnel.push_back(tunnelShape);
	}
}



bool TestRom::isIntersecting(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2)
{
	float d1 = (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
	float d2 = (b2.x - b1.x) * (a2.y - b1.y) - (b2.y - b1.y) * (a2.x - b1.x);
	float d3 = (a2.x - a1.x) * (b1.y - a1.y) - (a2.y - a1.y) * (b1.x - a1.x);
	float d4 = (a2.x - a1.x) * (b2.y - a1.y) - (a2.y - a1.y) * (b2.x - a1.x);

	return (d1 * d2 < 0) && (d3 * d4 < 0);
}

sf::Vector2f TestRom::intersectionPoint(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2)
{
	float A1 = a2.y - a1.y;
	float B1 = a1.x - a2.x;
	float C1 = A1 * a1.x + B1 * a1.y;

	float A2 = b2.y - b1.y;
	float B2 = b1.x - b2.x;
	float C2 = A2 * b1.x + B2 * b1.y;

	float det = A1 * B2 - A2 * B1;

	if (det == 0)
		return sf::Vector2f(); // 선분이 평행한 경우

	float x = (B2 * C1 - B1 * C2) / det;
	float y = (A1 * C2 - A2 * C1) / det;

	return sf::Vector2f(x, y);
}

bool TestRom::isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, sf::Vector2f& intersection)
{
	sf::Vector2f b1(rect.left, rect.top);
	sf::Vector2f b2(rect.left + rect.width, rect.top);
	sf::Vector2f b3(rect.left, rect.top + rect.height);
	sf::Vector2f b4(rect.left + rect.width, rect.top + rect.height);

	if (isIntersecting(a1, a2, b1, b2))
	{
		intersection = intersectionPoint(a1, a2, b1, b2);
		return true;
	}
	if (isIntersecting(a1, a2, b1, b3))
	{
		intersection = intersectionPoint(a1, a2, b1, b3);
		return true;
	}
	if (isIntersecting(a1, a2, b2, b4))
	{
		intersection = intersectionPoint(a1, a2, b2, b4);
		return true;
	}
	if (isIntersecting(a1, a2, b3, b4))
	{
		intersection = intersectionPoint(a1, a2, b3, b4);
		return true;
	}

	return false;
}






/*
for (int i = 0; i < tileRoom.size(); ++i)
	{
		for (int k = 0; k < passages.size(); ++k)
		{
			sf::Vector2f pos;
			if (isIntersecting(tileRoom[i].map->vertexArray.getBounds(), passages[k].from, passages[k].to, pos))
			{
				bool isNotPos = false;
				for (auto& pushPos : positions)
				{
					if (pushPos == pos)
					{
						isNotPos = true;
						break;
					}
				}
				if (!isNotPos)
				{
					sf::Vector2f center = tileRoom[i].map->GetStartPos();
					if (pos.x > center.x)
					{
						pos.x -= tileRoom[i].map->GetTileSize().x * 0.5f;
					}
					if (pos.x < center.x)
					{
						pos.x += tileRoom[i].map->GetTileSize().x * 0.5f;
					}
					if (pos.y > center.y)
					{
						pos.y -= tileRoom[i].map->GetTileSize().y * 0.5f;
					}
					if (pos.y < center.y)
					{
						pos.y += tileRoom[i].map->GetTileSize().y * 0.5f;
					}
					positions.push_back(pos);
				}
			}
		}
	}
*/