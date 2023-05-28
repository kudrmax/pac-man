#pragma once

#include "entity.h"
#include <memory>
#include <vector>

class IDynamicEntuty;
class IStaticEntuty;

struct GameContext {
    enum State { INGAME, WIN, LOST } state = INGAME;
    std::vector<std::unique_ptr<IDynamicEntuty>> dynamic_objects;
    std::vector<std::unique_ptr<IStaticEntuty>> static_objects;
    PacMan pacman();
    GameContext clone();
};

class ContextManager{
public:
    void save_current_context();
    void restore_previous_context();
    void set_context(GameContext contex);
    GameContext get_context();
private:
    GameContext m_context;
};