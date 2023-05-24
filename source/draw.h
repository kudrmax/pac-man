#pragma once

#include "state.h"
#include "command.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

//class IStateManager;
//
//struct IMyDrawable {
//    virtual void draw_into(sf::RenderWindow& window) = 0;
//    virtual ~IMyDrawable() = default;
//};
//
//struct Button : public IMyDrawable, public sf::RectangleShape {
//public:
//    using RectangleShape::RectangleShape;
//    void draw_into(sf::RenderWindow& window) override {};
////    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size, ISelectCommand* ptr_command);
//    void select() {};
//    void unselect() {};
//    bool is_selected() { return true; };
//    bool is_position_in(sf::Vector2f pos) { return true; };
//    void push() {};
//private:
//    bool m_is_selected = false;
//    sf::Font m_font;
//    sf::Text m_text;
//    RectangleShape m_rectangle;
//};
//
//struct Menu : public IMyDrawable {
//    Menu(IStateManager* state_manager) {};
//    void draw_into(sf::RenderWindow& window) override;
////    void process_mouse(sf::Vector2f pos, bool is_pressed) {};
//private:
//    std::vector<Button*> m_buttons;
////    ISelectCommand* m_ptr_command;
//};



