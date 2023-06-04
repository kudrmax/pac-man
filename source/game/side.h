#pragma once

#include "maze.h"

struct IRoomSide : public IMyDrawable {
//    virtual void enter(IEntity* entity) = 0;
    virtual void call() = 0;
    virtual ~IRoomSide() = default;
};

sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle);

class Pass : public IRoomSide {
public:
    Pass(Room* room1, Room* room2) : m_room1(room1), m_room2(room2) {}
    void draw_into(sf::RenderWindow& window) override { /* empty */
//        std::cout << "draw_into in Pass\n";
    }
    void call() override {};
//    void enter(IEntity* entity) override;
private:
    Room* m_room1;
    Room* m_room2;
};

class Wall : public IRoomSide {
public:
    Wall(Room* room) : m_room(room) {};
    void draw_into(sf::RenderWindow& window) override {
//        this->call();
        prepare_to_draw(m_room);
        window.draw(m_line, 2, sf::Lines);
//        std::cout << "draw_into in Wall\n";
    };
    void call() override {
        std::cout << std::endl;
        std::cout << "m_line[0] = { " << m_line[0].position.x << ", " << m_line[0].position.y << " }\n";
        std::cout << "m_line[1] = { " << m_line[1].position.x << ", " << m_line[1].position.y << " }\n";
        std::cout << std::endl;
    };
//    void enter(IEntity* entity) override;
    void prepare_to_draw(Room* room) {
        auto dir = room->get_direction(this);
        auto size = room->get_size() / 2;
        auto pos = room->get_position();
        auto vec = sf::Vector2f{ -size, 0 };
        auto rotate_vec = rotate_vector2f(vec, 90 * static_cast<int>(dir));
        auto rotate_vec2 = rotate_vector2f(rotate_vec, 90);
        auto pos0 = pos + rotate_vec + rotate_vec2;
        auto pos1 = pos + rotate_vec - rotate_vec2;

//        std::cout << "dir = " << dir << std::endl;
//        std::cout << "size = " << size << std::endl;
//        std::cout << "pos = { " << pos.x << ", " << pos.y << " }\n";
//        std::cout << "vec = { " << vec.x << ", " << vec.y << " }\n";
//        std::cout << "rotate_vec = { " << rotate_vec.x << ", " << rotate_vec.y << " }\n";
//        std::cout << "rotate_ve2 = { " << rotate_vec2.x << ", " << rotate_vec2.y << " }\n";
//        std::cout << "pos0 = { " << pos0.x << ", " << pos0.y << " }\n";
//        std::cout << "pos1 = { " << pos1.x << ", " << pos1.y << " }\n";

        m_line[0] = pos0;
        m_line[1] = pos1;
    }
private:
    Room* m_room;
    sf::Vertex m_line[2];
};