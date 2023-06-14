#pragma once

#include <array>
#include <exception>
#include "../i_draw.h"
#include "side.h"
//#include "side.h"

//class IRoomSide;

class Room : public IMyDrawable {
public:
    enum Direction {
        INVALID = -1, LEFT, UP, RIGHT, DOWN
    };
    explicit Room(float size, bool is_fillable = true);
    void set_side(Direction side, std::shared_ptr<IRoomSide>&& ptr_room_side);
    void set_position(sf::Vector2f position) { m_rectangle.setPosition(position); }
    float get_size() { return m_rectangle.getSize().x; }
    sf::Vector2f get_position() { return m_rectangle.getPosition(); }
    IRoomSide* get_side(Direction side) { return m_sides[side].get(); };
    Direction get_direction(IRoomSide* ptr_room_side);
    void draw_into(sf::RenderWindow& window) override;
    bool is_fillable() { return m_is_fillable; }
    void set_fillable(bool is_fillable) { m_is_fillable = is_fillable; }
private:
    sf::RectangleShape m_rectangle;
    std::array<std::shared_ptr<IRoomSide>, 4> m_sides;
    bool m_is_fillable;
};

class Maze : public IMyDrawable {
public:
    Maze() = default;
    explicit Maze(std::vector<std::unique_ptr<Room>>& rooms) : m_rooms(std::move(rooms)) {};
    void draw_into(sf::RenderWindow& window) override;
private:
    std::vector<std::unique_ptr<Room>> m_rooms;
};
