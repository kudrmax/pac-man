#pragma once

#include "maze.h"

struct IRoomSide : public IMyDrawable {
//    virtual void enter(IEntity* entity) = 0;
    virtual void call() = 0;
    virtual ~IRoomSide() = default;
};

class Pass : public IRoomSide {
public:
    Pass(Room room1, Room room2) : m_room1(std::move(room1)), m_room2(std::move(room2)) {}
    void draw_into(sf::RenderWindow& window) override { /* empty */ }
    void call(){};
//    void enter(IEntity* entity) override;
private:
    Room m_room1;
    Room m_room2;
};

sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle);

class Wall : public IRoomSide {
public:
    Wall(Room& room) : m_room(room) {
        auto size = room.get_size() / 2;
        auto pos = room.get_position();
        auto dir = room.get_direction(this);
        std::cout << "dir = { " << dir << " }\n";
        auto vec = pos + sf::Vector2f{ -size, 0 };

        std::cout << "vec_old = { " << vec.x << ", " << vec.y << " }\n";
        auto pos1 = rotate_vector2f(vec, 90 * static_cast<int>(dir));
        auto pos2 = rotate_vector2f(pos1, 90);
        auto pos3 = rotate_vector2f(pos2, -90);
        pos2 = pos1 + pos2;
        pos3 = pos1 + pos3;
        std::cout << "pos2 = { " << pos2.x << ", " << pos2.y << " }\n";
        std::cout << "pos3 = { " << pos3.x << ", " << pos3.y << " }\n";
        m_line[0] = pos2;
        m_line[1] = pos3;
    };
    void draw_into(sf::RenderWindow& window) override;
    void call() {
        std::cout << std::endl;
        std::cout << "m_line[0] = { " << m_line[0].position.x << ", " << m_line[0].position.y << " }\n";
        std::cout << "m_line[1] = { " << m_line[1].position.x << ", " << m_line[1].position.y << " }\n";
        std::cout << std::endl;
    };
//    void enter(IEntity* entity) override;
private:
    Room m_room;
    sf::Vertex m_line[2];
};