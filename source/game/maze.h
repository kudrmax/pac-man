#pragma once

#include <array>
#include <exception>
#include "../i_draw.h"
//#include "side.h"
//#include "side.h"

class IRoomSide;

class Room : public IMyDrawable {
public:
    enum Direction {
        INVALID = -1, LEFT, UP, RIGHT, DOWN
    };
    explicit Room(float size) : m_rectangle({ size, size }) {
        m_rectangle.setOrigin(size / 2, size / 2);
    }
    void set_side(Direction side, std::shared_ptr<IRoomSide> ptr_room_side) {
        if (side > -1) {
            m_sides[side] = ptr_room_side;
//            m_sides[side] = std::move(ptr_room_side);
        } else {
            std::cout << "error= -1\n";
            throw std::runtime_error("error");
        }
//        std::cout << "DONE\n";
    };
    void set_position(sf::Vector2f position) { m_rectangle.setPosition(position); }
    float get_size() { return m_rectangle.getSize().x; }
    sf::Vector2f get_position() { return m_rectangle.getPosition(); }
    std::shared_ptr<IRoomSide> get_side(Direction side) { return m_sides[side]; };
    Direction get_direction(IRoomSide* ptr_room_side);
    void draw_into(sf::RenderWindow& window) override;
private:
    sf::RectangleShape m_rectangle;
    std::array<std::shared_ptr<IRoomSide>, 4> m_sides;
};

class Maze : public IMyDrawable {
public:
//    Maze() = default;
    explicit Maze(std::vector<std::shared_ptr<Room>> rooms) : m_rooms(std::move(rooms)) {
//        std::cout << "Maze(room)" << std::endl;
    };
    void draw_into(sf::RenderWindow& window) override;
private:
    std::vector<std::shared_ptr<Room>> m_rooms;
};
