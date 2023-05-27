#pragma once

//#include "main.h"
#include "draw.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class IState {
public:
    IState(IStateManager* state_manager) : m_state_manager(state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    IStateManager* m_state_manager = nullptr;
};

struct IStateManager {
    virtual void set_next_state(std::unique_ptr<IState> state) = 0;
    virtual ~IStateManager() = default;
};

class IWindowKeeper {
public:
    IWindowKeeper(sf::VideoMode mode, const std::string& title) : m_window(mode, title) {};
protected:
    virtual void event_handling() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~IWindowKeeper() = default;
protected:
    sf::RenderWindow m_window;
};

class ExitState : public IState {
public:
    using IState::IState;
    bool do_step() override { return false; };
};

//////////

struct ISelectCommand {
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};

struct IChangeStateCommand : public ISelectCommand {
    IChangeStateCommand(IStateManager& state_manager) : m_state_manager(&state_manager) {}; // СПОРНО
protected:
    IStateManager* m_state_manager;
};

struct ExitCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute();
};

struct GameCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute();
};

//////////


class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager& state_manager, const std::string& window_title);
    bool do_step() override;
    void event_handling() override;
    void update() override;
    void render() override;
private:
    Menu m_menu;
};

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