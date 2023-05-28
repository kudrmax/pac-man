#pragma once

#include "../draw.h"
#include "maze.h"

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
    void set_location(std::shared_ptr<Room> ptr_room) override {};
    std::shared_ptr<Room> get_location() override {};
//    void move(Room::Direction direction) { m_location->get_side(direction)->enter(this); };
//    std::unique_ptr<IEntity> clone();
};