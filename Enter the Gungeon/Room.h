#pragma once

const int min_width = 150; // 최소 너비
const int min_height = 100; // 최소 높이
class Room 
{
protected:
    struct Rect {
        float x, y, width, height;
    };

    struct Passage {
        sf::Vector2f from, to;
    };

    struct Divider {
        sf::Vector2f start, end;
    };

    std::vector<Rect> rooms;
    std::vector<Passage> passages;
    std::vector<Divider> dividers;

    bool drawTest;
    std::vector<sf::RectangleShape> tiles;
    std::vector<bool> connected;
public:
    Room();
    void Divide(Rect rect, int depth);
    sf::Vector2f Center(const Rect& room) {return { room.x + room.width / 2, room.y + room.height / 2 };}
    sf::Vector2f oneFourth(const Rect& room) { return { room.x + room.width*0.25f, room.y + room.height *0.25f }; }
    void ConnectRooms(const Rect& r1, const Rect& r2);
    void Draw(sf::RenderWindow& window);
    float Distance(const Rect& r1, const Rect& r2);
    void PrintSize();
    void ConnectClosestRooms();
    void ValidateAndModifyPassages();
    bool IsPassageValid(const Passage& passage);
    void AdjustPassage(Passage& passage);
    std::vector<Rect>& GetRoom() { return rooms; }
    Rect& GetRoomIndex(int value) { return rooms[value]; }
    int LineSize() { return dividers.size(); }
    int length = 0;
};

