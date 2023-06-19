#pragma once

#include "../i_draw.h"
#include "maze.h"
#include "i_visitor.h"
#include <time.h>
#include <stdlib.h>
#include <random>
//#include "../config.h"
//#include "game_event.h"
//#include "game_event.h"
//#include "side.h"
//#include "../config.h"

//class IRoomSide;

class IEntity : public IMyDrawable {
public:
    void set_location(Room& ptr_room) { m_location = &ptr_room; };
    Room& get_location() { return *m_location; };
protected:
    Room* m_location;
};

struct IStaticEntity : public IEntity, public IVisitable {
    virtual std::unique_ptr<IStaticEntity> clone() const = 0;
};

struct IDynamicEntity : public IEntity, public IVisitable {
    virtual std::unique_ptr<IDynamicEntity> clone() const = 0;
    virtual void action() = 0;
};

struct Food : public IStaticEntity {
    void draw_into(sf::RenderWindow& window) override;
    std::unique_ptr<IStaticEntity> clone() const override { return std::make_unique<Food>(*this); };
    std::unique_ptr<IGameEvent> accept(IVisitor& ptr_visitor) override;
};

struct Enemy : public IDynamicEntity {
    void draw_into(sf::RenderWindow& window) override;
    std::unique_ptr<IDynamicEntity> clone() const override { return std::make_unique<Enemy>(*this); };
    std::unique_ptr<IGameEvent> accept(IVisitor& ptr_visitor) override;
    void action() override;
    void set_previous_location() { m_previous_location = m_location; };
private:
    inline static std::mt19937 s_generator{ std::random_device{}() };
    inline static std::uniform_int_distribution s_side_choice{ 0, 3 };
    sf::Clock m_time_before_action;
    Room* m_previous_location;
};

struct PacMan : public IEntity, public IVisitor {
    void draw_into(sf::RenderWindow& window) override;
    void move(Room::Direction direction);
    std::unique_ptr<IGameEvent> visit(Food& ptr_food) override;
    std::unique_ptr<IGameEvent> visit(Enemy& ptr_food) override;
};