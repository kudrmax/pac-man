#pragma once

#include "../i_draw.h"
#include "maze.h"
//#include "side.h"
//#include "../config.h"

//class IRoomSide;

class IEntity : public IMyDrawable {
public:
    void set_location(std::shared_ptr<Room> ptr_room)  { m_location = ptr_room; };
    std::shared_ptr<Room> get_location()  { return m_location;};
    virtual ~IEntity() = default;
protected:
    std::shared_ptr<Room> m_location;
};

struct IStaticEntity : public IEntity {
    virtual std::unique_ptr<IStaticEntity> clone() = 0;
};

struct IDynamicEntity : public IEntity {
    virtual std::unique_ptr<IDynamicEntity> clone() = 0;
};

struct Food : public IStaticEntity {
    void draw_into(sf::RenderWindow& window) override {
        float r = 3;
        auto food = sf::CircleShape(r);
        food.setFillColor(sf::Color::Green);
        food.setOrigin(r, r);
        food.setPosition(m_location->get_position());
        window.draw(food);
    };
    std::unique_ptr<IStaticEntity> clone() override {};
};

struct Enemy : public IDynamicEntity {
    std::unique_ptr<IDynamicEntity> clone() override {};
};

struct PacMan : public IEntity {
    void draw_into(sf::RenderWindow& window) override {
        float r = 20;
        auto circle = sf::CircleShape(r);
        circle.setFillColor(sf::Color::Yellow);
        circle.setOrigin(r, r);
        circle.setPosition(m_location->get_position());
        window.draw(circle);
    }
    void call() {
        std::cout << " m_location->get_position() = { " << m_location->get_position().x << ", "
                  << m_location->get_position().x << " }\n";
    }
    void move(Room::Direction direction);
};