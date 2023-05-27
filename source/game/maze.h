#pragma once

#include "../draw.h"

class IRoomSide;

class Room : public IMyDrawable {
public:
    enum Direction { INVALID = -1, LEFT, RIGHT, UP, DOWN };
    Room(float size);
    void set_side(Direction side, IRoomSide* ptr_room_side);
    void set_position(sf::Vector2f position);
    float get_size();
    sf::Vector2f get_position();
    IRoomSide* get_side(Direction side);
    Direction get_direction(IRoomSide* ptr_room_side);
    void draw_into(sf::RenderWindow& window) override;
private:
    sf::RectangleShape m_rectangle;
    IRoomSide* m_sides[4];
};

struct IEntity : public IMyDrawable{
public:
    virtual void set_location(Room* ptr_room) = 0;
    virtual Room* get_location() = 0;
//    void draw_into(sf::RenderWindow& window) override;
protected:
    Room* m_location;
};

class Maze : public IMyDrawable {
public:
    Maze(std::vector<std::unique_ptr<Room>> rooms);
private:
    std::vector<std::unique_ptr<Room>> m_rooms;
};

struct IRoomSide : public IMyDrawable {
    virtual void enter(IEntity* entity) = 0;
//    void draw_into(sf::RenderWindow& window) override;
};

class Pass : public IRoomSide {
public:
    Pass(Room room1 , Room room2);
    void draw_into(sf::RenderWindow& window) override {};
private:
    Room m_room1;
    Room m_room2;
};

class Wall : public IRoomSide {
public:
    Wall(Room room);
    void draw_into(sf::RenderWindow& window) override;
private:
    Room m_room;
    sf::Vertex m_line[2];
};