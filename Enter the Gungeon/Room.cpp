#include "stdafx.h"
#include "Room.h"

Room::Room()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    Rect initial = { 0, 0,5000, 5000 };
    Divide(initial,4);

    sf::Vector2i  startPos = { (int)initial.x ,(int)initial.y };
    int widht = initial.width /25;
    int height = initial.height /25;
   int size = rooms.size() / 2;
   std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
   //if (size <=7)
   //    rooms.resize(7);
   //else 
   //    rooms.resize(Utils::RandomRange(7, size));

    rooms.resize(10);


   connected.resize(rooms.size(), false);
   connected[0] = true;
   int currentRoom = 0;
   int count = 0;
   while (true)
   {
       int closestRoom = -1;
       float minDistance = std::numeric_limits<float>::max();

       // 가장 가까운 방을 찾습니다.
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

       // 더 이상 연결되지 않은 방이 없으면 종료합니다.
       if (closestRoom == -1)
       {
           lastRoom = currentRoom;
           break;
       }

       // 가장 가까운 방을 연결하고 다음 방을 찾습니다.

       connected[closestRoom] = true;
       currentRoom = closestRoom;
       if (count == rooms.size() / 2) 
           middlePoint = currentRoom;
       count++;
   }
}
 

const int tile_size = 25; // 타일의 크기

void Room::Divide(Rect rect, int depth)
{
    if (depth <= 0 || rect.width < 1.5 * min_width || rect.height < 1.5 * min_height)
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



void Room::PrintSize()
{
    for (size_t i = 0; i < rooms.size() ; ++i) {
        std::cout << i << "번째 x:" << rooms[i].width << "\t" << "y:" << rooms[i].height << std::endl;
    }

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

        for (const auto& divider : dividers)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = divider.start;
            line[1].position = divider.end;
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            window.draw(line);
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