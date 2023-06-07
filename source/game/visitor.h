#pragma once

//#include "game_event.h"
//#include "entity.h"

class IGameEvent;
class Food;
class Enemy;
#include <iostream>

struct IVisitor{
    virtual std::shared_ptr<IGameEvent> visit(Food* ptr_food) = 0;
    virtual std::shared_ptr<IGameEvent> visit(Enemy* ptr_food) = 0;
    virtual ~IVisitor() = default;
//    IGameEvent* visit(Enemy* ptr_enemy);
};

struct IVisitable{
    virtual std::shared_ptr<IGameEvent> accept(IVisitor* ptr_visitor) = 0;
    virtual ~IVisitable() = default;
};