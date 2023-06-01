#pragma once

#include "../i_state.h"
#include "../i_window.h"
#include "maze.h"
#include "game_contex.h"
#include "game_event.h"
#include "game_contex.h"


class GameState : public IState, public IWindowKeeper {
public:
//    using IState::IState;
    GameState(IStateManager* state_manager, const std::string& window_title);
//    void set_maze(Maze maze);
    void set_context(GameContext&& context);
    bool do_step() override;
    void event_handling() override;
    void update() override;
    void render() override;
    void call() override { std::cout << "GameState\n"; }
private:
//    void process_key_pressed(sf::Keyboard::Key key);
//    void process_event(std::unique_ptr<IGameEvent> ptr_event);
private:
    ContextManager m_context_manager;
//    Maze m_maze;
};