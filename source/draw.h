#pragma once

//#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class ISelectCommand;
class IStateManager;

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
    void push();
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
    std::unique_ptr<ISelectCommand> m_ptr_command = nullptr;
};

struct Menu : public IMyDrawable {
public:
    Menu(IStateManager& state_manager);
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

