#pragma once

#include "entity.h"
#include <memory>
#include <vector>
#include <stack>


struct GameContext {
    GameContext clone() const;
    enum State {
        INGAME, WIN, LOST
    };
    PacMan pacman;
    State state = INGAME;
    std::vector<std::unique_ptr<IDynamicEntity>> dynamic_objects;
    std::vector<std::unique_ptr<IStaticEntity>> static_objects;
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