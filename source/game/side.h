#pragma once

#include "../i_draw.h"

class Room;
class IEntity;

struct IRoomSide : public IMyDrawable {
    virtual bool enter(IEntity& entity) = 0;
};

class Pass : public IRoomSide {
public:
    Pass(Room& room1, Room& room2) : m_room1(room1), m_room2(room2) {}
    void draw_into(sf::RenderWindow& window) override { /* do noting */ }
    bool enter(IEntity& entity) override;
private:
    Room& m_room1;
    Room& m_room2;
};

class Wall : public IRoomSide {
public:
    explicit Wall(Room& room) : m_room(room) {};
    void draw_into(sf::RenderWindow& window) override;
    bool enter(IEntity& entity) override;
private:
    void prepare_to_draw(Room& room);
    sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle);
private:
    Room& m_room;
    sf::Vertex m_line[2];
};