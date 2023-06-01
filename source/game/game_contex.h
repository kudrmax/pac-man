#pragma once

#include "entity.h"
#include <memory>
#include <vector>
#include <stack>


struct GameContext {
    enum State {
        INGAME, WIN, LOST
    } state = INGAME;
    std::vector<std::unique_ptr<IDynamicEntity>> dynamic_objects;
    std::vector<std::unique_ptr<IStaticEntity>> static_objects;
    PacMan pacman();
    GameContext clone();
};

class ContextManager {
public:
    void save_current_context();
    void restore_previous_context();
    void set_context(GameContext&& contex);
    GameContext get_context();
private:
    GameContext m_context;
    std::stack<GameContext> m_history;
//    std::vector<GameContext> m_history;
};