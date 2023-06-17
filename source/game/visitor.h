#pragma once

#include <memory>

class IGameEvent;
class Food;
class Enemy;

struct IVisitor{
    virtual std::unique_ptr<IGameEvent> visit(Food& ptr_food) = 0;
    virtual std::unique_ptr<IGameEvent> visit(Enemy& ptr_food) = 0;
    virtual ~IVisitor() = default;
};

struct IVisitable{
    virtual std::unique_ptr<IGameEvent> accept(IVisitor& ptr_visitor) = 0;
    virtual ~IVisitable() = default;
};