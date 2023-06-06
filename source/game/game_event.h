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
        std::cout << "ptr_entity = " << ptr_entity << std::endl;
        std::cout << "m_ptr_entity = " << m_ptr_entity << std::endl;
    };
    DeleteStaticEntity() : m_ptr_entity() {};
    void handle(GameContext* context) override {
        std::cout << "context = " << context << std::endl;
        auto& vec = context->static_objects;
        std::cout << "vec in handle = " << &vec << std::endl;
        auto it = std::find_if(vec.begin(), vec.end(), [&](auto el) { return el.get() == m_ptr_entity; });
        vec.erase(it);
//        vec.erase(vec.begin());
//        std::shared_ptr<IStaticEntity> delete_el;
//        for (auto el: vec) {
//            if (el.get() == m_ptr_entity) {
//                vec.erase()
//                break;
//            }
//        }
//        if (!delete_el) {
//            std::remove(vec.begin(), vec.end(), delete_el);
//            std::cout << "deleted\n";
//        }
    }
private:
    IStaticEntity* m_ptr_entity;
};