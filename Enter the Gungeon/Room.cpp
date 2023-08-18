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
   if (size == 0) rooms.resize(Utils::RandomRange(1, 5));
   else rooms.resize(Utils::RandomRange(3, size));

    for (size_t i = 0; i < rooms.size() - 1; ++i) {
        ConnectRooms(rooms[i], rooms[i + 1]);
    }
 
}

void Room::Divide(Rect rect, int depth)
{
    if (depth <= 0 || rect.width < min_width*2 || rect.height < min_height*2) {
        // 중심에 기반한 작은 방 생성
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


    // 사각형을 수평 또는 수직으로 분할
    if (rand() % 2 == 0) {
        // 수평 분할
        if (hDivider < 2 * min_height) return;
        dividers.push_back({ { rect.x, rect.y + hDivider }, { rect.x + rect.width, rect.y + hDivider } });
        Divide({ rect.x, rect.y, rect.width, hDivider }, depth - 1);
        Divide({ rect.x, rect.y + hDivider, rect.width, rect.height - hDivider }, depth - 1);
    }
    else {
        // 수직 분할
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

    // L-모양 통로 생성
    passages.push_back({ c1, {c2.x, c1.y} });
    passages.push_back({ {c2.x, c1.y}, c2 });
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

void Room::Draw(sf::RenderWindow& window)
{

    // 여기서 구분자를 그림
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

        // 여기서 통로를 그림
        /*for (const auto& passage : passages) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = passage.from;
            line[1].position = passage.to;
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }*/
        for (const auto& divider : dividers)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = divider.start;
            line[1].position = divider.end;
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            window.draw(line);
        }
        for (int i = 0;i < length;++i)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = passages[i].from;
            line[1].position = passages[i].to;
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }
       /* for (const auto& tile : tiles)
        {
            window.draw(tile);
        }*/
    }
}
