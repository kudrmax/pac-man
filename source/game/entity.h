#pragma once

#include "../i_draw.h"
#include "maze.h"
#include "visitor.h"
//#include "game_event.h"
//#include "game_event.h"
//#include "side.h"
//#include "../config.h"

//class IRoomSide;

class IEntity : public IMyDrawable {
public:
    void set_location(std::shared_ptr<Room> ptr_room) { m_location = ptr_room; };
    std::shared_ptr<Room> get_location() { return m_location; };
    virtual ~IEntity() = default;
protected:
    std::shared_ptr<Room> m_location;
};

struct IStaticEntity : public IEntity, public IVisitable {
    virtual std::unique_ptr<IStaticEntity> clone() = 0;
};

struct IDynamicEntity : public IEntity, public IVisitable {
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
    std::shared_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override;
};

struct Enemy : public IDynamicEntity {
    void draw_into(sf::RenderWindow& window) override {
        float r = 10;
        auto enemy = sf::CircleShape(r);
        enemy.setFillColor(sf::Color::Red);
        enemy.setOrigin(r, r);
        enemy.setPosition(m_location->get_position());
        window.draw(enemy);
    };
    std::unique_ptr<IDynamicEntity> clone() override {};
    std::shared_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override {
        return ptr_visitor->visit(this);
    };
};

struct PacMan : public IEntity, public IVisitor {
    void draw_into(sf::RenderWindow& window) override;
    void move(Room::Direction direction);
    std::shared_ptr<IGameEvent> visit(Food* ptr_food) override;
    std::shared_ptr<IGameEvent> visit(Enemy* ptr_food) override;
};