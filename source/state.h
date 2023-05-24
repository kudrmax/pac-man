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
    explicit IState(IStateManager* state_manager){};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    IStateManager* m_state_manager;
};


class IWindowKeeper {
public:
    IWindowKeeper(sf::VideoMode mode, std::string title){};
protected:
    virtual void event_handling() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~IWindowKeeper() = default;
protected:
    sf::RenderWindow m_window{ sf::VideoMode(800, 800), "SFML" };
};

//class ExitState : public IState {
//public:
//    bool do_step() override { return false; };
//};





class IStateManager;

struct IMyDrawable {
    virtual void draw_into(sf::RenderWindow& window) = 0;
    virtual ~IMyDrawable() = default;
};

struct Button : public IMyDrawable, public sf::RectangleShape {
public:
    using RectangleShape::RectangleShape;
    void draw_into(sf::RenderWindow& window) override {};
//    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size, ISelectCommand* ptr_command);
    void select() {};
    void unselect() {};
    bool is_selected() { return true; };
    bool is_position_in(sf::Vector2f pos) { return true; };
    void push() {};
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
};

struct Menu : public IMyDrawable {
    Menu(IStateManager* state_manager) {};
    void draw_into(sf::RenderWindow& window) override {};
//    void process_mouse(sf::Vector2f pos, bool is_pressed) {};
private:
    std::vector<Button*> m_buttons;
//    ISelectCommand* m_ptr_command;
};
















class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager* state_manager, std::string window_title) :
            IWindowKeeper({800, 600}, window_title), m_menu(state_manager) {};
    void event_handling() override {};
    void update() override {};
    void render() override {};
    bool do_step() override { return true; };
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