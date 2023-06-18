#include "button.h"
#include "../config.h"
#include "button_command.h"

bool Button::is_position_in(const sf::Vector2f& position) {
    auto delta = m_rectangle.getPosition() - position;
    return (std::abs(delta.x) < m_rectangle.getSize().x / 2) &&
           (std::abs(delta.y) < m_rectangle.getSize().y / 2);
}

void Button::select() {
    m_is_selected = true;
};

void Button::unselect() {
    m_is_selected = false;
};

void Button::push() {
    m_ptr_command->execute();
};

void Button::draw_into(sf::RenderWindow& window) {
    if (m_is_selected)
        m_rectangle.setFillColor(config::BUTTON_COLOR_SELECTION);
    else
        m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
    window.draw(m_rectangle);
    window.draw(m_text);
}


Button::Button(const sf::Vector2f& button_center_pos,
               const sf::Vector2f& button_size,
               const std::string& text,
               size_t font_size,
               std::unique_ptr<ISelectCommand>&& ptr_command) {
    m_rectangle.setSize(button_size);
    m_rectangle.setOrigin(button_size.x / 2, button_size.y / 2);
    m_rectangle.setPosition(button_center_pos);
    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
    m_rectangle.setOutlineColor(config::BUTTON_COLOR_FRAME);
    m_rectangle.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);
    if (!m_font.loadFromFile(config::FONT_FILE))
        throw std::runtime_error("No such file in directory");
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(font_size);
    m_text.setLetterSpacing(1);
    auto textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_text.setPosition(button_center_pos);
    m_text.setFillColor(config::BUTTON_COLOR_TEXT);
    m_text.setOutlineColor(config::BUTTON_COLOR_FRAME);
    m_text.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);
    m_ptr_command = std::move(ptr_command);
}