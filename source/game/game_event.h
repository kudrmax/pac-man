#pragma once

#include "entity.h"
#include <memory>

#include "game_contex.h"

class GameContext;

struct IGameEvent {
    virtual void handle(GameContext* context) = 0;
    virtual ~IGameEvent() = default;
};

struct WinGame : public IGameEvent {
    void handle(GameContext* context) override {}
};

struct LostGame : public IGameEvent {
    void handle(GameContext* context) override {}
};

struct DeleteStaticEntity : public IGameEvent {
    DeleteStaticEntity(IStaticEntity* ptr_entity) {
        m_ptr_entity = ptr_entity;
    };
    DeleteStaticEntity() : m_ptr_entity() {};
    void handle(GameContext* context) override {
        auto& vec = context->static_objects;
        std::shared_ptr<IStaticEntity> delete_el;
        for (auto el: vec) {
            if (&*el == &*m_ptr_entity) {
                delete_el = el;
//                std::cout << "found\n";
                break;
            }
        }
        if (!delete_el) {
            std::remove(vec.begin(), vec.end(), delete_el);
            std::cout << "deleted\n";
        }
    }
private:
    IStaticEntity* m_ptr_entity;
};