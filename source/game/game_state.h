#pragma once

#include "../i_state.h"
#include "../i_window.h"

class GameState : public IState, public IWindowKeeper {
public:
//    using IState::IState;
    GameState(IStateManager& state_manager, const std::string& window_title);
//    void set_maze(Maze maze);
//    void set_context(GameContext context);
    bool do_step() override { return true; };
    void event_handling() override {};
    void update() override {};
    void render() override {};
private:
//    void process_key_pressed(code);
//    void process_event(IGameEvent* ptr_event);
private:
//    ContextManager m_context_manager;
//    Maze m_maze;
};