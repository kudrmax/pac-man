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
    explicit IState(std::unique_ptr<IStateManager> state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    std::unique_ptr<IStateManager> m_state_manager;
};


class IWindowKeeper {
public:
    IWindowKeeper(sf::VideoMode mode, const std::string& title) : m_window(mode, "test") {};
protected:
    virtual void event_handling() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~IWindowKeeper() = default;
protected:
//    sf::RenderWindow m_window{ sf::VideoMode(800, 800), "SFML" };
    sf::RenderWindow m_window;
};

class ExitState : public IState {
public:
    bool do_step() override { return false; };
};


class IStateManager;

struct IMyDrawable {
    virtual void draw_into(sf::RenderWindow& window) = 0;
    virtual ~IMyDrawable() = default;
};

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


struct Button : public IMyDrawable, public sf::RectangleShape {
public:
    using RectangleShape::RectangleShape;
    void draw_into(sf::RenderWindow& window) override {
        window.draw(m_rectangle);
        window.draw(m_text);
        window.display();
        std::cout << "draw_into() in Button\n";
    };
    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
           ISelectCommand* ptr_command) {
        m_rectangle.setSize(button_size);
        m_rectangle.setOrigin(button_size.x / 2, button_size.y / 2);
        m_rectangle.setPosition(button_center_pos);
        m_rectangle.setFillColor(sf::Color::Yellow);
        m_text.setString(text);
        m_text.setOrigin(button_size.x / 2, button_size.y / 2);
        m_text.setPosition(button_center_pos);
        m_text.setFillColor(sf::Color::Blue);
        std::cout << "I'm here\n";
    };
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
    ISelectCommand* m_ptr_command;
};

struct Menu : public IMyDrawable {
//    Menu(std::unique_ptr<IStateManager> state_manager) {};
    Menu(IStateManager* state_manager) {
//        auto temp = Button({50,50}, { 50,50} , "Exit", 16, nullptr);
        m_buttons.push_back(std::make_unique<Button>(Button({50,50}, { 50,50} , "Exit", 16, nullptr)));
    };
    void draw_into(sf::RenderWindow& window) override {
        for(auto& ptr_button: m_buttons)
            ptr_button->draw_into(window);
    };
    void process_mouse(sf::Vector2f pos, bool is_pressed) {};
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};


class SelectState : public IState, public IWindowKeeper {
public:
    using IWindowKeeper::IWindowKeeper;
    SelectState(IStateManager* state_manager, const std::string& window_title) :
            m_menu(state_manager),
            IWindowKeeper({ 800, 800 }, window_title) {};
    void event_handling() override {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                auto exit_ptr = std::make_unique<ExitState>();;
                return;
            }
        }
    };
    void update() override {};
    void render() override {
//        m_window.clear(sf::Color(0x222222FF));
//        auto circle = sf::CircleShape();
//        circle.setRadius(60);
//        circle.setFillColor(sf::Color::Red);
//        m_window.draw(circle);
//        m_window.display();
        m_menu.draw_into(m_window);
    };
    bool do_step() override {
//        std::cout << "SelectState\n";
        event_handling();
        update();
        render();
        return true;
    };
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