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
    Wall() : m_room(100) {};
    Wall(Room room);
    void draw_into(sf::RenderWindow& window) override;
//    void enter(IEntity* entity) override;
private:
    Room m_room;
    sf::Vertex m_line[2];
};