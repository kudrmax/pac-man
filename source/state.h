#pragma once

#include "menu.h"
#include "draw.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class IStateManager;
//class Menu;

class IState {
public:
    IState() = default;
    IState(std::unique_ptr<IStateManager> state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    std::unique_ptr<IStateManager> m_state_manager;
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
    bool do_step() override { return false; };
};

//////////

struct ISelectCommand {
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};

struct IChangeStateCommand : public ISelectCommand {
    IChangeStateCommand(IStateManager state_manager);
protected:
    std::unique_ptr<IStateManager> m_state_manager;
};

struct ExitCommand : public IChangeStateCommand {
    void execute() {};
};

struct GameCommand : public IChangeStateCommand {
//    GameCommand(IStateManager state_manager, GameBuilderDirector* ptr_director);
    void execute() {};
};

//////////

struct IMyDrawable {
    virtual void draw_into(sf::RenderWindow& window) = 0;
    virtual ~IMyDrawable() = default;
};

struct Button : public IMyDrawable, public sf::RectangleShape {
public:
    using RectangleShape::RectangleShape;
    void draw_into(sf::RenderWindow& window) override;
    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
           ISelectCommand* ptr_command);
//    void select() {};
//    void unselect() {};
//    bool is_selected() { return true; };
//    bool is_position_in(sf::Vector2f pos) { return true; };
//    void push() {};
private:
//    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
    ISelectCommand* m_ptr_command;
};

struct Menu : public IMyDrawable {
public:
    Menu(IStateManager* state_manager);
    void draw_into(sf::RenderWindow& window) override;
//    void process_mouse(sf::Vector2f pos, bool is_pressed) {};
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};


class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager* state_manager, const std::string& window_title);
    void event_handling() override;
    void update() override {};
    void render() override { m_menu.draw_into(m_window); };
    bool do_step() override;
private:
    Menu m_menu;
};

//class GameState : public IState, public IWindowKeeper {
//public:
////    GameState(IStateManager* state_manager, std::string window_title);
////    void set_maze(Maze maze);
////    void set_context(GameContext context);
//    bool do_step() override { return true; };
//    void event_handling() override {};
//    void update() override {};
//    void render() override {};
//private:
////    void process_key_pressed(code);
////    void process_event(IGameEvent* ptr_event);
//private:
////    ContextManager m_context_manager;
////    Maze m_maze;
//};