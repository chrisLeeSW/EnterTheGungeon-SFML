#pragma once

const int min_width = 400; // 최소 너비
const int min_height = 400; // 최소 높이
class Room 
{
protected:
    struct Rect {
        float x, y, width, height;
    };

    struct Divider {
        sf::Vector2f start, end;
    };

    std::vector<Rect> rooms;
    std::vector<Divider> dividers;

    bool drawTest;
    std::vector<bool> connected;

    int lastRoom = 0;
    int middlePoint = 0;
public:
    Room();
    void Divide(Rect rect, int depth);
    sf::Vector2f Center(const Rect& room) {return { room.x + room.width / 2, room.y + room.height / 2 };}
    sf::Vector2f oneFourth(const Rect& room) { return { room.x + room.width*0.25f, room.y + room.height *0.25f }; }
    void Draw(sf::RenderWindow& window);
    void PrintSize();
    std::vector<Rect>& GetRoom() { return rooms; }
    Rect& GetRoomIndex(int value) { return rooms[value]; }

    float Distance(const Rect& r1, const Rect& r2);
    int GetLastRoom() { return lastRoom; }
    int GetMidRoom() { return middlePoint; }
};

