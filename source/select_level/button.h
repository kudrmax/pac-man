#pragma once

#include "../i_draw.h"
#include "button_command.h"

struct Button : public IMyDrawable, public sf::RectangleShape {
public:
    using RectangleShape::RectangleShape;
    Button(const sf::Vector2f& button_center_pos,
           const sf::Vector2f& button_size,
           const std::string& text,
           size_t font_size,
           std::unique_ptr<ISelectCommand>&& ptr_command);
    void draw_into(sf::RenderWindow& window) override;
    void select();
    void unselect();
    bool is_selected() const { return m_is_selected; };
    bool is_position_in(const sf::Vector2f& position);
    void push();
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    RectangleShape m_rectangle;
    std::unique_ptr<ISelectCommand> m_ptr_command;
};