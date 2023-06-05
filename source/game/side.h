#pragma once

#include "maze.h"
#include "entity.h"

class IEntity;

struct IRoomSide : public IMyDrawable {
    virtual void enter(IEntity* entity) = 0;
    virtual void call() = 0;
    virtual ~IRoomSide() = default;
};

sf::Vector2f rotate_vector2f(const sf::Vector2f& vec, int angle);

class Pass : public IRoomSide {
public:
    Pass(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2) : m_room1(room1), m_room2(room2) {}
    void draw_into(sf::RenderWindow& window) override { /* empty */ }
    void call() override {};
    void enter(IEntity* entity) override { entity->set_location(m_room2); };
private:
    std::shared_ptr<Room> m_room1;
    std::shared_ptr<Room> m_room2;
};

class Wall : public IRoomSide {
public:
    Wall(std::shared_ptr<Room> room) : m_room(room) {};
    void draw_into(sf::RenderWindow& window) override;
    void call() override;
    void enter(IEntity* entity) override {};
    void prepare_to_draw(std::shared_ptr<Room> room);
private:
    std::shared_ptr<Room> m_room;
    sf::Vertex m_line[2];
};