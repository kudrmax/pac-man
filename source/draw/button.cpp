#include "button.h"
#include "../config.h"
#include "../select_level/button_command.h"

bool Button::is_position_in(sf::Vector2f pos) {
    auto delta = m_rectangle.getPosition() - pos;
    return (std::abs(delta.x) < m_rectangle.getSize().x / 2) &&
           (std::abs(delta.y) < m_rectangle.getSize().y / 2);
}

void Button::select() {
    m_is_selected = true;
    m_rectangle.setFillColor(config::BUTTON_COLOR_SELECTION);
};
void Button::unselect() {
    m_is_selected = false;
    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
};

void Button::push() { m_ptr_command->execute(); };

void Button::draw_into(sf::RenderWindow& window) {
//    process_button();
    window.draw(m_rectangle);
    window.draw(m_text);
}

Button::Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
               std::unique_ptr<ISelectCommand> ptr_command) {
    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
    m_rectangle.setSize(button_size);
    m_rectangle.setOrigin(button_size.x / 2, button_size.y / 2);
    m_rectangle.setPosition(button_center_pos);
//    if (!m_font.loadFromFile("Cyrilik.TTF"))
//        throw std::runtime_error("No such file in directory");
//    m_text.setString(text);
//    m_text.setFont(m_font);
//    m_text.setPosition(1000, 500);
//    m_text.setFillColor(sf::Color::Blue);
//    m_text.setCharacterSize(font_size);
    m_ptr_command = std::move(ptr_command);
}
