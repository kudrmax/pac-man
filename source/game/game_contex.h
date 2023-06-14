#pragma once

#include "entity.h"
#include <memory>
#include <vector>
#include <list>
#include <stack>


struct GameContext {
    GameContext clone() {
        GameContext new_context;
        new_context.pacman = pacman;
        new_context.state = state;
        for(const auto& dynamic_object : dynamic_objects)
            new_context.dynamic_objects.push_back(dynamic_object->clone());
        for(const auto& static_object : static_objects)
            new_context.static_objects.push_back(static_object->clone());
        return new_context;
    };
    enum State {
        INGAME, WIN, LOST
    };
    PacMan pacman;
    State state = INGAME;
    std::vector<std::shared_ptr<IDynamicEntity>> dynamic_objects;
    std::vector<std::shared_ptr<IStaticEntity>> static_objects;
};

class ContextManager {
public:
    void save_current_context();
    void restore_previous_context();
    void set_context(GameContext&& context) { m_context = std::move(context); };
    GameContext& get_context() { return m_context; };
private:
    GameContext m_context;
    std::stack<GameContext> m_history;
};