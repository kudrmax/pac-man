#pragma once

#include "../i_state.h"
#include "../i_window.h"
#include "maze.h"
#include "game_contex.h"
#include "game_event.h"
//#include "../config.h"


class GameState : public IState, public IWindowKeeper {
public:
    GameState(IStateManager& state_manager, const std::string& window_title, const sf::VideoMode& mode);
    void set_maze(Maze&& maze) { m_maze = std::move(maze); };
    void set_context(GameContext&& context);
    bool do_step() override;
    void event_handling() override;
    void update() override;
    void render() override;
private:
    void process_key_pressed(sf::Keyboard::Key key);
    void process_event(std::unique_ptr<IGameEvent> event){
        event->handle(m_context_manager.get_context());
    };
private:
    void clear_background();
private:
    ContextManager m_context_manager;
    Maze m_maze;
    bool m_do_not_update = false;
};