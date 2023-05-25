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
    bool do_step() override { return false; };
};

//////////

struct ISelectCommand {
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};

struct IChangeStateCommand : public ISelectCommand {
    IChangeStateCommand(IStateManager* state_manager) : m_state_manager(state_manager) {};
protected:
    std::unique_ptr<IStateManager> m_state_manager;
};

struct ExitCommand : public IChangeStateCommand {
    using IChangeStateCommand::IChangeStateCommand;
    void execute() {
        m_state_manager->set_next_state(std::unique_ptr<ExitState>());
    };
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
    Button() = default;
    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
           std::unique_ptr<ISelectCommand> ptr_command);
//    void select() {};
//    void unselect() {};
//    bool is_selected() { return true; };
    bool is_position_in(sf::Vector2f position) {
        sf::Vector2f delta = position - getPosition();
        return std::abs(delta.x) < (getSize().x / 2) && std::abs(delta.y) < (getSize().y / 2);
    };
    void push() {
        m_ptr_command->execute();
    };
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
//    ISelectCommand* m_ptr_command;
    std::unique_ptr<ISelectCommand> m_ptr_command;
};

struct Menu : public IMyDrawable {
public:
    Menu(IStateManager* state_manager);
    void draw_into(sf::RenderWindow& window) override;
    void process_mouse(sf::Vector2f pos, bool is_pressed) {
        if (is_pressed) {
            std::cout << "Pushed\n";
            m_buttons[0]->push();
        }
    };
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};


class SelectState : public IState, public IWindowKeeper {
public:
    SelectState(IStateManager* state_manager, const std::string& window_title);
    void event_handling() override;
    void update() override {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            auto position_int = sf::Mouse::getPosition(m_window);
            auto position_float = m_window.mapPixelToCoords(position_int);
            std::cout << (event.type == sf::Event::MouseButtonPressed);
            m_menu.process_mouse(position_float, event.type == sf::Event::MouseButtonPressed);
            m_menu.draw_into(m_window);
        }
    };
    void render() override { m_window.display(); };
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