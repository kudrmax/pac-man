#pragma once

#include "../draw.h"
#include "button_command.h"

struct Button : public IMyDrawable, public sf::RectangleShape {
public:
    using RectangleShape::RectangleShape;
    void draw_into(sf::RenderWindow& window) override;
    Button() = default;
    Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
           std::unique_ptr<ISelectCommand> ptr_command);
    void select();
    void unselect();
    bool is_selected() { return m_is_selected; };
    bool is_position_in(sf::Vector2f position);
    void push();
//    void process_button();
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
    std::unique_ptr<ISelectCommand> m_ptr_command;
};