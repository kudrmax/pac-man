#pragma once

#include "../i_draw.h"
#include "maze.h"
//#include "side.h"
//#include "../config.h"

//class IRoomSide;

class IEntity : public IMyDrawable {
public:
    virtual void set_location(std::shared_ptr<Room> ptr_room) = 0;
    virtual std::shared_ptr<Room> get_location() = 0;
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
    void set_location(std::shared_ptr<Room> ptr_room) override {};
    std::shared_ptr<Room> get_location() override {};
    std::unique_ptr<IStaticEntity> clone() override {};
};

struct Enemy : public IDynamicEntity {
    void set_location(std::shared_ptr<Room> ptr_room) override {};
    std::shared_ptr<Room> get_location() override {};
    std::unique_ptr<IDynamicEntity> clone() override {};
};

struct PacMan : public IEntity {
    void draw_into(sf::RenderWindow& window) {
        float r = 20;
        auto circle = sf::CircleShape(r);
        circle.setFillColor(sf::Color::Magenta);
        circle.setOrigin(r, r);
        circle.setPosition(m_location->get_position());
//        std::cout << "draw_into in PacMan\n";
//        this->call();
        window.draw(circle);
    }
    void set_location(std::shared_ptr<Room> ptr_room) override { m_location = ptr_room; };
    std::shared_ptr<Room> get_location() override {
//        this->call();
        return m_location;
    };
    void call() {
        std::cout << " m_location->get_position() = { " << m_location->get_position().x << ", "
                  << m_location->get_position().x << " }\n";
    }
    void move(Room::Direction direction);
//    std::unique_ptr<IEntity> clone();
};