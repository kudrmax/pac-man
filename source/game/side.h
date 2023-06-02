#pragma once

#include "maze.h"

struct IRoomSide : public IMyDrawable {
//    virtual void enter(IEntity* entity) = 0;
    virtual ~IRoomSide() = default;
};

class Pass : public IRoomSide {
public:
    Pass(Room room1, Room room2) : m_room1(std::move(room1)), m_room2(std::move(room2)) {}
    void draw_into(sf::RenderWindow& window) override { /* empty */ }
//    void enter(IEntity* entity) override;
private:
    Room m_room1;
    Room m_room2;
};

class Wall : public IRoomSide {
public:
    Wall(Room& room) : m_room(room) {
        auto size = room.get_size() / 2;
        auto pos = room.get_position();
        auto dir = room.get_direction(this);
        auto vec = pos + sf::Vector2f{ -size, 0 };

        std::cout << "vec = { " << vec.x << ", " << vec.y << " }\n";
//        sf::Transform transform;
//        transform.transformPoint(vec);
//        vec = transform.rotate(90, pos);
//        std::cout << "vec = { " << vec.x << ", " << vec.y << " }\n";
//        std::cout << "transform = { " << transform.getMatrix() << " }\n";
        sf::Transform translation;
        translation.translate(pos);
        sf::Transform rotation;
        rotation.rotate(90);
        sf::Transform transform = translation * rotation;
        vec = transform.transformPoint(vec);
        std::cout << "vec = { " << vec.x << ", " << vec.y << " }\n";
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