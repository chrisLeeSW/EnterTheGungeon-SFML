#include "stdafx.h"
#include "Room.h"

Room::Room()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    Rect initial = { -1500, -1500,5000, 5000 };
    Divide(initial,5);

    sf::Vector2i  startPos = { -1500 ,-1500 };
    int widht = 5000 /50;
    int height = 5000 /50;

    for (int i = 0;i < height;++i)
    {
        for (int k = 0;k < widht;++k)
        {
            sf::RectangleShape shape;
            shape.setSize({ 48.f,48.f });
            shape.setFillColor(sf::Color::Transparent);
            shape.setPosition(startPos.x + (k*50), startPos.y + (i * 50));
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Yellow);
            tiles.push_back(shape);
        }
    }
   int size = rooms.size();
   std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
  // if (size == 0) rooms.resize(Utils::RandomRange(1, 5));
   //else rooms.resize(Utils::RandomRange(3, size));
   rooms.resize(10);

   connected.resize(rooms.size(), false);
   connected[0] = true;
   int currentRoom = 0;
   while (true)
   {
       int closestRoom = -1;
       float minDistance = std::numeric_limits<float>::max();

       // ���� ����� ���� ã���ϴ�.
       for (size_t i = 1; i < rooms.size(); ++i)
       {
           if (!connected[i])
           {
               float dist = Distance(rooms[currentRoom], rooms[i]);
               if (dist < minDistance)
               {
                   minDistance = dist;
                   closestRoom = i;
               }
           }
       }

       // �� �̻� ������� ���� ���� ������ �����մϴ�.
       if (closestRoom == -1)
       {
           break;
       }

       // ���� ����� ���� �����ϰ� ���� ���� ã���ϴ�.
       ConnectRooms(rooms[currentRoom], rooms[closestRoom]);
       connected[closestRoom] = true;
       currentRoom = closestRoom;
   }
}

void Room::Divide(Rect rect, int depth)
{
    if (depth <= 0 || rect.width < min_width*2 || rect.height < min_height*2) {
        // �߽ɿ� ����� ���� �� ����
        Rect room;
        room.width = rect.width *0.75;
        room.height = rect.height * 0.75 ;
        room.x = rect.x + (rect.width - room.width) * 0.75;
        room.y = rect.y + (rect.height - room.height) * 0.75;
        rooms.push_back(room);
        return;
    }


    float hDivider = rect.height / 2;
    float wDivider = rect.width / 2;


    // �簢���� ���� �Ǵ� �������� ����
    if (rand() % 2 == 0) {
        // ���� ����
        if (hDivider < 2 * min_height) return;
        dividers.push_back({ { rect.x, rect.y + hDivider }, { rect.x + rect.width, rect.y + hDivider } });
        Divide({ rect.x, rect.y, rect.width, hDivider }, depth - 1);
        Divide({ rect.x, rect.y + hDivider, rect.width, rect.height - hDivider }, depth - 1);
    }
    else {
        // ���� ����
        if (wDivider < 2 * min_width) return;
        dividers.push_back({ { rect.x + wDivider, rect.y }, { rect.x + wDivider, rect.y + rect.height } });
        Divide({ rect.x, rect.y, wDivider, rect.height }, depth - 1);
        Divide({ rect.x + wDivider, rect.y, rect.width - wDivider, rect.height }, depth - 1);
    }

}

void Room::ConnectRooms(const Rect& r1, const Rect& r2)
{
    sf::Vector2f c1 = Center(r1);
    sf::Vector2f c2 = Center(r2);
    // L-��� ��� ����
    passages.push_back({ c1, {c2.x, c1.y} });
    passages.push_back({ {c2.x, c1.y}, c2 });

}
bool Room::IsPassageValid(const Passage& passage)
{
    for (const auto& room : rooms)
    {
        if (room.x <= passage.from.x && passage.from.x <= room.x + room.width &&
            room.y <= passage.from.y && passage.from.y <= room.y + room.height)
        {
            return false;
        }
        if (room.x <= passage.to.x && passage.to.x <= room.x + room.width &&
            room.y <= passage.to.y && passage.to.y <= room.y + room.height)
        {
            return false;
        }
    }
    return true;
}
void Room::AdjustPassage(Passage& passage)
{
    // ��θ� �����Ϸ��� �ٸ� ��� ��ġ�� �ʵ��� �� ���׸�Ʈ�� ��ġ�� �����ؾ� �մϴ�.
    // �� �ڵ�� ��� ��ġ�� �ʵ��� ���׸�Ʈ�� �̵���Ű�� ����� �����ϴ� ���Դϴ�.
    for (const auto& room : rooms)
    {
        if (room.x <= passage.from.x && passage.from.x <= room.x + room.width &&
            room.y <= passage.from.y && passage.from.y <= room.y + room.height)
        {
            passage.from.x = room.x - 1.0f;
        }
        if (room.x <= passage.to.x && passage.to.x <= room.x + room.width &&
            room.y <= passage.to.y && passage.to.y <= room.y + room.height)
        {
            passage.to.x = room.x - 1.0f;
        }
    }
}
void Room::PrintSize()
{
    for (size_t i = 0; i < rooms.size() ; ++i) {
        std::cout << i << "��° x:" << rooms[i].width << "\t" << "y:" << rooms[i].height << std::endl;
    }
    for (size_t i = 0; i < dividers.size(); ++i) {
        std::cout << i << "��° x:" << dividers[i].start.x <<"/"<<dividers[i].start.y << "\t" << "y:" << dividers[i].end.x<< "/"<<dividers[i].end.y << std::endl;
    }
}

void Room::ConnectClosestRooms()
{
    std::set<int> unconnected; // ������� ���� ���� �ε��� ����
    std::set<std::pair<int, int>> connectedPairs; // ����� �� �� ����
    for (size_t i = 0; i < rooms.size(); ++i)
    {
        unconnected.insert(i);
    }

    int currentRoomIndex = 0; // ���� �� �ε���
    unconnected.erase(currentRoomIndex); // ���� ���� ����� ������ ����

    // ��� ���� ����� ������ �ݺ�
    while (!unconnected.empty())
    {
        float min_distance = std::numeric_limits<float>::max();
        int closest_room = -1;

        sf::Vector2f c1 = Center(rooms[currentRoomIndex]);

        // ���� ������� ���� �� �� ���� ����� ���� ã��
        for (int nextRoomIndex : unconnected)
        {
            sf::Vector2f c2 = Center(rooms[nextRoomIndex]);
            float distance = std::sqrt(std::pow(c2.x - c1.x, 2) + std::pow(c2.y - c1.y, 2));

            // �̹� ����� ������ Ȯ��
            std::pair<int, int> roomPair = std::make_pair(std::min(currentRoomIndex, nextRoomIndex),
                std::max(currentRoomIndex, nextRoomIndex));
            if (connectedPairs.find(roomPair) == connectedPairs.end() && distance < min_distance)
            {
                min_distance = distance;
                closest_room = nextRoomIndex;
            }
        }

        // ���� ����� ��� ����
        if (closest_room != -1)
        {
            ConnectRooms(rooms[currentRoomIndex], rooms[closest_room]);
            unconnected.erase(closest_room); // ����� �� ����
            connectedPairs.insert(std::make_pair(std::min(currentRoomIndex, closest_room),
                std::max(currentRoomIndex, closest_room))); // ����� �� �� �߰�
            currentRoomIndex = closest_room; // ���� ������ ���� ���� ������ ����
        }
    }

    ///

    //std::vector<std::pair<float, std::pair<int, int>>> distances;
    //// �� ���� �߽����� ����ϰ� �ٸ� ����� �Ÿ��� ����մϴ�.
    //for (size_t i = 0; i < rooms.size(); ++i)
    //{
    //    sf::Vector2f c1 = Center(rooms[i]);
    //    for (size_t j = i + 1; j < rooms.size(); ++j)
    //    {
    //        sf::Vector2f c2 = Center(rooms[j]);
    //        float distance = std::sqrt(std::pow(c2.x - c1.x, 2) + std::pow(c2.y - c1.y, 2));
    //        distances.push_back({ distance, {i, j} });
    //    }
    //}

    //// �Ÿ��� �������� ������������ �����մϴ�.
    //std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b)
    //    {
    //        return a.first < b.first;
    //    });

    //// ���� ����� �波�� �����մϴ�.
    //for (const auto& d : distances)
    //{
    //    int i = d.second.first;
    //    int j = d.second.second;
    //    ConnectRooms(rooms[i], rooms[j]);
    //}
}

void Room::ValidateAndModifyPassages()
{
    std::vector<Passage> newPassages;
    for (const auto& passage : passages)
    {
        bool fromIsValid = false;
        bool toIsValid = false;
        for (const auto& room : rooms)
        {
            if (passage.from.x >= room.x && passage.from.x <= room.x + room.width &&
                passage.from.y >= room.y && passage.from.y <= room.y + room.height)
            {
                fromIsValid = true;
            }
            if (passage.to.x >= room.x && passage.to.x <= room.x + room.width &&
                passage.to.y >= room.y && passage.to.y <= room.y + room.height)
            {
                toIsValid = true;
            }
        }

        if (fromIsValid && toIsValid)
        {
            newPassages.push_back(passage);
        }
    }
    passages = newPassages;
}


void Room::Draw(sf::RenderWindow& window)
{

    // ���⼭ �����ڸ� �׸�
    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Insert))
    {
        drawTest = !drawTest;
    }
    if (drawTest)
    {
        for (const auto& room : rooms) {
            sf::RectangleShape rect;
            rect.setPosition(room.x, room.y);
            rect.setSize({ room.width, room.height });
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);
        }

        // ���⼭ ��θ� �׸�
        /*
        for (const auto& passage : passages) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = passage.from;
            line[1].position = passage.to;
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }
        
        */
        for (const auto& divider : dividers)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = divider.start;
            line[1].position = divider.end;
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            window.draw(line);
        }
       /* for (int i = 0;i < length;++i)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = passages[i].from;
            line[1].position = passages[i].to;
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }*/
       /* for (const auto& tile : tiles)
        {
            window.draw(tile);
        }*/
    }
}

float Room::Distance(const Rect& r1, const Rect& r2)
{
    sf::Vector2f c1 = Center(r1);
    sf::Vector2f c2 = Center(r2);
    float dx = c2.x - c1.x;
    float dy = c2.y - c1.y;
    return std::sqrt(dx * dx + dy * dy);
}



/*
std::vector<sf::Vector2f> Intersection(const sf::FloatRect& rect, const sf::Vector2f& start, const sf::Vector2f& end);
std::vector<sf::Vector2f> TestRom::Intersection(const sf::FloatRect& rect, const sf::Vector2f& start, const sf::Vector2f& end)
{

    // ���簢���� �𼭸� ��ǥ�� ���
    float left = rect.left;
    float right = rect.left + rect.width;
    float top = rect.top;
    float bottom = rect.top + rect.height;

    // ������ �������� ���: y = mx + b
    float m = (end.y - start.y) / (end.x - start.x);
    float b = start.y - m * start.x;

    // ���簢���� �� ���� ������� ������ �˻�
    // ���� ��
    float y = m * left + b;
    if (y >= top && y <= bottom && ((y >= start.y && y <= end.y) || (y <= start.y && y >= end.y)))
    {
        intersections.emplace_back(left, y);
    }

    // ������ ��
    y = m * right + b;
    if (y >= top && y <= bottom && ((y >= start.y && y <= end.y) || (y <= start.y && y >= end.y)))
    {
        intersections.emplace_back(right, y);
    }

    // ��� ��
    float x = (top - b) / m;
    if (x >= left && x <= right && ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x)))
    {
        intersections.emplace_back(x, top);
    }

    // �ϴ� ��
    x = (bottom - b) / m;
    if (x >= left && x <= right && ((x >= start.x && x <= end.x) || (x <= start.x && x >= end.x)))
    {
        intersections.emplace_back(x, bottom);
    }
    return intersections;
}


*/



//�ϵ��ڵ��� ������ �Ϻ� �̻���
//{
        //	sf::RectangleShape startShape;
        //	sf::Vector2f startpos = passages[lineCount].from;
        //	startShape.setSize({ 25.f,25.f });
        //	Utils::SetOrigin(startShape, Origins::MC);
        //	int t = lineCount + 1;
        //	if (t > passages.size()) t = passages.size();
        //	{
        //		if (passages[lineCount].from.x > passages[lineCount].to.x)
        //		{
        //			startpos.x -= tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f - (tileRoom[currentRoom].map->GetTileSize().x * 0.5f);
        //		}
        //		else if (passages[lineCount].from.x < passages[lineCount].to.x)
        //		{
        //			startpos.x += tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f - (tileRoom[currentRoom].map->GetTileSize().x * 0.5f);
        //		}
        //		else if (passages[lineCount].from.y > passages[lineCount + 1].to.y)
        //		{
        //			startpos.y -= tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5 - (tileRoom[currentRoom].map->GetTileSize().y * 0.5f);
        //		}
        //		else if (passages[lineCount].from.y < passages[lineCount + 1].to.y)
        //		{
        //			startpos.y += tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5f - (tileRoom[currentRoom].map->GetTileSize().y * 0.5f);
        //		}
        //	}
        //	/*else
        //	{
        //		if (passages[lineCount].from.x > passages[lineCount].to.x)
        //		{
        //			startpos.x -= tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f - tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
        //		}
        //		else if (passages[lineCount].from.x < passages[lineCount].to.x)
        //		{
        //			startpos.x += tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f + tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
        //		}
        //		else if (passages[lineCount].from.y > passages[lineCount].to.y)
        //		{
        //			startpos.y -= tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5 - tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
        //		}
        //		else if (passages[lineCount].from.y < passages[lineCount].to.y)
        //		{
        //			startpos.y += tileRoom[currentRoom].map->vertexArray.getBounds().height * 0.5f + tileRoom[currentRoom].map->GetTileSize().x * 0.5f;
        //		}
        //	}*/
        //	startShape.setPosition(startpos);
        //	startShape.setFillColor(sf::Color::Blue);
        //	lineCount++;
        //	tunnel.push_back(startShape);
        //	std::cout << startpos.x << "\t" << startpos.y << std::endl;
        //	std::cout << tileRoom[currentRoom].map->vertexArray.getBounds().width * 0.5f << std::endl;
        //	sf::RectangleShape endShpae;
        //	sf::Vector2f endpos = passages[lineCount].to;
        //	endShpae.setSize({ 25.f,25.f });
        //	Utils::SetOrigin(endShpae, Origins::MC);
        //	{
        //		if (passages[lineCount].to.x > passages[lineCount].from.x)
        //		{
        //			endpos.x += tileRoom[closestRoom].map->vertexArray.getBounds().width * 0.5f - (tileRoom[closestRoom].map->GetTileSize().x * 0.5f);
        //		}
        //		else if (passages[lineCount].to.x < passages[lineCount].from.x)
        //		{
        //			endpos.x -= tileRoom[closestRoom].map->vertexArray.getBounds().width * 0.5f - (tileRoom[closestRoom].map->GetTileSize().x * 0.5f);
        //		}
        //		else if (passages[lineCount].to.y < passages[lineCount - 1].from.y)
        //		{
        //			endpos.y += tileRoom[closestRoom].map->vertexArray.getBounds().height * 0.5f - (tileRoom[closestRoom].map->GetTileSize().y * 0.5f);
        //		}
        //		else if (passages[lineCount].to.y > passages[lineCount - 1].from.y)
        //		{
        //			endpos.y -= tileRoom[closestRoom].map->vertexArray.getBounds().height * 0.5f - (tileRoom[closestRoom].map->GetTileSize().y * 0.5f);
        //		}
        //	}
        //	endShpae.setPosition(endpos);
        //	endShpae.setFillColor(sf::Color::Red);
        //	lineCount++;
        //	tunnel.push_back(endShpae);
        //}

// �ͳ� ����



//for (const auto& passage : passages)
    //{
    //	sf::Vector2f start, end;
    //	bool foundStart = false, foundEnd = false;

    //	// ����� �������� ������ ã���ϴ�.
    //	for (const auto& door : doorShape)
    //	{
    //		if (!foundStart && passage.from == door.getPosition())
    //		{
    //			start = passage.from;
    //			foundStart = true;
    //		}
    //		if (!foundEnd && passage.to == door.getPosition())
    //		{
    //			end = passage.to;
    //			foundEnd = true;
    //		}
    //		if (foundStart && foundEnd)
    //		{
    //			break;
    //		}
    //	}

    //	// �������� ������ ã�Ҵٸ� �ͳ��� �����մϴ�.
    //	if (foundStart && foundEnd)
    //	{
    //		CreateTunnel(start, end);
    //	}
    //}
    /*for (int i = 0; i < positions.size() - 1; ++i)
    {
        CreateTunnel(positions[i], positions[i + 1]);
    }*/
//
/*
int tunnelCount = 0;
	int doorCount = 1;
	lineCount = 0;
    */
//while (tunnelCount != doorShape.size()-1)
    //{
    //	
    //	sf::Vector2f pos;
    //	//if (isIntersecting(tileRoom[doorCount].map->vertexArray.getBounds() ,positions[tunnelCount], passages[lineCount].to, pos))
    //	if (isIntersecting(tileRoom[doorCount].map->vertexArray.getBounds(), positions[tunnelCount], passages[lineCount].to, pos))
    //	{
    //		
    //		tunnelCount++;
    //		if (lineCount % 2 == 0 && lineCount !=0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].to);
    //		else if(lineCount % 2 == 1 && lineCount != 0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].from);
    //		else if (lineCount == 0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].to);
    //		//doorCount++;
    //	}
    //	else 
    //	{
    //		if(lineCount % 2 == 0 && lineCount != 0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].to);
    //		else if(lineCount % 2 == 1 && lineCount != 0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].from);
    //		else if (lineCount == 0)
    //			CreateTunnel(positions[tunnelCount], passages[lineCount++].to);
    //		
    //	}
    //}
    //  �ڵ尡 ����
//
//
// 
    //int a=0;
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
    //			else CreateTunnel(positions[i - 1], passages[a].to);
    //		}
    //		else
    //		{
    //			if (a % 2 == 1)
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
    //				else  CreateTunnel(positions[i - 1], passages[a].to);
    //			}
    //			else
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
    //				else CreateTunnel(positions[i - 1], passages[a].to);
    //			}
    //		}
    //		a++;
    //	}
    //	/*for (int k = 0; k < passages.size(); ++k)
    //	{
    //		sf::Vector2f pos;
    //		if (k == 0)
    //		{
    //			if (isIntersecting(doorShape[i].getGlobalBounds(), positions[i - 1], passages[k].to, pos))
    //			{
    //				CreateTunnel(positions[i - 1], passages[k].to);
    //				break;
    //			}
    //			else CreateTunnel(positions[i - 1], passages[k].to);
    //		}
    //		else
    //		{
    //			if (k % 2 == 1)
    //			{
    //				if (isIntersecting(doorShape[i].getGlobalBounds(), passages[k].from, passages[k].to, pos))
    //				{
    //					CreateTunnel(passages[k].from, passages[k].to);
    //					break;
    //				}
    //			}
    //			else
    //			{
    //				if (isIntersecting(doorShape[i].getGlobalBounds(), passages[k].from, passages[k].to, pos))
    //				{
    //					CreateTunnel(passages[k].from, passages[k].to);
    //					break;
    //				}
    //			}
    //		}
    //	}*/
    //}


/*
for (int i = 0; i < positions.size() - 1; ++i)
    {
        sf::Vector2f startPos = positions[i];
        sf::Vector2f endPos = positions[i + 1];

        if (startPos.x > endPos.x)
            startPos.x -= 12.5f;
        if (startPos.x < endPos.x)
            startPos.x += 12.5f;
        if (startPos.y > endPos.y)
            startPos.y -= 12.5f;
        if (startPos.y < endPos.y)
            startPos.y += 12.5f;
        CreateTunnel(startPos,endPos);
    }
// //���� �̻��ϰ� ���ư��� ������ ���� 
*/