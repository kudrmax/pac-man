#pragma once

#include <array>
#include "../i_draw.h"

class IRoomSide;
class Pass;

class Room : public IMyDrawable {
public:
    enum Direction {
        INVALID = -1, LEFT, RIGHT, UP, DOWN
    };
    explicit Room(float size) : m_rectangle({ size, size }) {}
    void set_side(Direction side, std::shared_ptr<IRoomSide> ptr_room_side) {
        if (side > -1)
            m_sides[side] = std::move(ptr_room_side);
    };
    void set_position(sf::Vector2f position) { m_rectangle.setPosition(position); }
    float get_size() { return m_rectangle.getSize().x; }
    sf::Vector2f get_position() { return m_rectangle.getPosition(); }
    std::shared_ptr<IRoomSide> get_side(Direction side) { return m_sides[side]; };
    Direction get_direction(IRoomSide* ptr_room_side);
    void draw_into(sf::RenderWindow& window) override {};
private:
    sf::RectangleShape m_rectangle;
    std::array<std::shared_ptr<IRoomSide>, 4> m_sides;
};

//struct IEntity : public IMyDrawable {
//public:
//    virtual void set_location(std::shared_ptr<Room> ptr_room) = 0;
//    virtual std::shared_ptr<Room> get_location() = 0;
//protected:
//    Room* m_location;
//};

class Maze : public IMyDrawable {
public:
    explicit Maze(std::vector<std::shared_ptr<Room>> rooms) : m_rooms(std::move(rooms)) {};
    void draw_into(sf::RenderWindow& window) override {};
private:
    std::vector<std::shared_ptr<Room>> m_rooms;
};

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
    explicit Wall(Room room);
    void draw_into(sf::RenderWindow& window) override {};
//    void enter(IEntity* entity) override;
private:
    Room m_room;
    sf::Vertex m_line[2];
};