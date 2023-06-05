#pragma once

//#include "game_event.h"
//#include "entity.h"

class IGameEvent;
class Food;
#include <iostream>

struct IVisitor{
    virtual std::unique_ptr<IGameEvent> visit(Food* ptr_food) = 0;
    virtual ~IVisitor() = default;
//    IGameEvent* visit(Enemy* ptr_enemy);
};

struct IVisitable{
    virtual std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) = 0;
    virtual ~IVisitable() = default;
};