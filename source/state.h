#pragma once

#include "draw.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class IStateManager;
//class Menu;

class IState {
public:
    explicit IState(IStateManager* state_manager);
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    IStateManager* m_state_manager;
};


class IWindowKeeper {
public:
//    IWindowKeeper(type mode, std::string title);
protected:
    virtual void event_handling() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~IWindowKeeper() = default;
protected:
    sf::RenderWindow m_window{ sf::VideoMode(800, 800), "SFML" };
};

class ExitState : public IState {
public:
    bool do_step() override { return false; };
};

class SelectState : public IState, public IWindowKeeper {
public:
//    SelectState(type state_manager, type window_title);
    void event_handling(){};
    void update(){};
    void render(){};
    bool do_step() override {};
private:
//    Menu m_menu;
};

class GameState : public IState, public IWindowKeeper {
public:
//    GameState(IStateManager* state_manager, std::string window_title);
//    void set_maze(Maze maze);
//    void set_context(GameContext context);
    bool do_step() override {};
private:
//    void process_key_pressed(code);
//    void process_event(IGameEvent* ptr_event);
private:
//    ContextManager m_context_manager;
//    Maze m_maze;
};