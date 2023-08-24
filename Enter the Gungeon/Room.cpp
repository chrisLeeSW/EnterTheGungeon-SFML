#include "stdafx.h"
#include "Room.h"

Room::Room()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    Rect initial = { 0, 0,3000, 3000 };
    Divide(initial,4);

    sf::Vector2i  startPos = { (int)initial.x ,(int)initial.y };
    int widht = initial.width /25;
    int height = initial.height /25;

    for (int i = 0;i < height;++i)
    {
        for (int k = 0;k < widht;++k)
        {
            sf::RectangleShape shape;
            shape.setSize({ 23.f,23.f });
            shape.setFillColor(sf::Color::Transparent);
            shape.setPosition(startPos.x + (k*25), startPos.y + (i * 25));
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Yellow);
            tiles.push_back(shape);
        }
    }
   int size = rooms.size() / 2;
   std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
   //if (size == 0) rooms.resize(Utils::RandomRange(1, 5));
   //else rooms.resize(Utils::RandomRange(3, size));

   rooms.resize(15);
}

const int tile_size = 25; // 타일의 크기

void Room::Divide(Rect rect, int depth)
{
    if (depth <= 0 || rect.width < 2 * tile_size || rect.height < 2 * tile_size)
    {
        // 중심에 기반한 작은 방 생성
        Rect room;
        room.width = (rect.width / tile_size) * tile_size;
        room.height = (rect.height / tile_size) * tile_size;
        room.x = rect.x + (rect.width - room.width) / 2;
        room.y = rect.y + (rect.height - room.height) / 2;
        rooms.push_back(room);
        return;
    }

    int hDivider = (rect.height / tile_size / 2) * tile_size;
    int wDivider = (rect.width / tile_size / 2) * tile_size;

    // 사각형을 수평 또는 수직으로 분할
    if (rand() % 2 == 0)
    {
        // 수평 분할
        if (hDivider < 2 * tile_size) return;
        dividers.push_back({ { rect.x, rect.y + hDivider }, { rect.x + rect.width, rect.y + hDivider } });
        Divide({ rect.x, rect.y, rect.width, (float)hDivider }, depth - 1);
        Divide({ rect.x, rect.y + hDivider, rect.width, rect.height - hDivider }, depth - 1);
    }
    else
    {
        // 수직 분할
        if (wDivider < 2 * tile_size) return;
        dividers.push_back({ { rect.x + wDivider, rect.y }, { rect.x + wDivider, rect.y + rect.height } });
        Divide({ rect.x, rect.y, (float)wDivider, rect.height }, depth - 1);
        Divide({ rect.x + wDivider, rect.y, rect.width - wDivider, rect.height }, depth - 1);
    }

}

void Room::ConnectRooms(const Rect& r1, const Rect& r2)
{
    sf::Vector2f c1 = Center(r1);
    sf::Vector2f c2 = Center(r2);
    // L-모양 통로 생성
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
    // 경로를 조정하려면 다른 방과 겹치지 않도록 각 세그먼트의 위치를 변경해야 합니다.
    // 이 코드는 방과 겹치지 않도록 세그먼트를 이동시키는 방법을 구현하는 예입니다.
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
        std::cout << i << "번째 x:" << rooms[i].width << "\t" << "y:" << rooms[i].height << std::endl;
    }
    for (size_t i = 0; i < dividers.size(); ++i) {
        std::cout << i << "번째 x:" << dividers[i].start.x <<"/"<<dividers[i].start.y << "\t" << "y:" << dividers[i].end.x<< "/"<<dividers[i].end.y << std::endl;
    }
}

void Room::ConnectClosestRooms()
{
    std::set<int> unconnected; // 연결되지 않은 방의 인덱스 집합
    std::set<std::pair<int, int>> connectedPairs; // 연결된 방 쌍 집합
    for (size_t i = 0; i < rooms.size(); ++i)
    {
        unconnected.insert(i);
    }

    int currentRoomIndex = 0; // 시작 방 인덱스
    unconnected.erase(currentRoomIndex); // 시작 방을 연결된 방으로 간주

    // 모든 방이 연결될 때까지 반복
    while (!unconnected.empty())
    {
        float min_distance = std::numeric_limits<float>::max();
        int closest_room = -1;

        sf::Vector2f c1 = Center(rooms[currentRoomIndex]);

        // 아직 연결되지 않은 방 중 가장 가까운 방을 찾음
        for (int nextRoomIndex : unconnected)
        {
            sf::Vector2f c2 = Center(rooms[nextRoomIndex]);
            float distance = std::sqrt(std::pow(c2.x - c1.x, 2) + std::pow(c2.y - c1.y, 2));

            // 이미 연결된 쌍인지 확인
            std::pair<int, int> roomPair = std::make_pair(std::min(currentRoomIndex, nextRoomIndex),
                std::max(currentRoomIndex, nextRoomIndex));
            if (connectedPairs.find(roomPair) == connectedPairs.end() && distance < min_distance)
            {
                min_distance = distance;
                closest_room = nextRoomIndex;
            }
        }

        // 가장 가까운 방과 연결
        if (closest_room != -1)
        {
            ConnectRooms(rooms[currentRoomIndex], rooms[closest_room]);
            unconnected.erase(closest_room); // 연결된 방 제거
            connectedPairs.insert(std::make_pair(std::min(currentRoomIndex, closest_room),
                std::max(currentRoomIndex, closest_room))); // 연결된 방 쌍 추가
            currentRoomIndex = closest_room; // 다음 연결할 방을 현재 방으로 설정
        }
    }
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

    // 여기서 구분자를 그림
    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Insert))
    {
        drawTest = !drawTest;
    }
    if (drawTest)
    {
      /*  for (const auto& room : rooms) {
            sf::RectangleShape rect;
            rect.setPosition(room.x, room.y);
            rect.setSize({ room.width, room.height });
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);
        }*/

        // 여기서 통로를 그림
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
       for (const auto& tile : tiles)
        {
            window.draw(tile);
        }
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
