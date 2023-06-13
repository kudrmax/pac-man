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
    m_rectangle.setFillColor(config::BUTTON_COLOR_SELECTION);
};
void Button::unselect() {
    m_is_selected = false;
    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
};

void Button::push() {
    m_ptr_command->execute();
};

void Button::draw_into(sf::RenderWindow& window) {
    window.draw(m_rectangle);
    window.draw(m_text);
}


Button::Button(const sf::Vector2f& button_center_pos, const sf::Vector2f& button_size, const std::string& text,
               size_t font_size,
               std::unique_ptr<ISelectCommand>&& ptr_command) {
    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
    m_rectangle.setSize(button_size);
    m_rectangle.setOrigin(button_size.x / 2, button_size.y / 2);
    m_rectangle.setPosition(button_center_pos);
    if (!m_font.loadFromFile("fonts/Cyrilik.TTF"))
        throw std::runtime_error("No such file in directory");
    sf::Font m_font2;
    if (!m_font2.loadFromFile("fonts/Cyrilik.TTF"))
        throw std::runtime_error("No such file in directory");
//    m_text.setFont(m_font);
//    m_text.setFont(m_font2);
    m_text.setString(text);
    m_text.setPosition(1000, 500);
    m_text.setFillColor(sf::Color::Blue);
    m_text.setCharacterSize(font_size);
    m_ptr_command = std::move(ptr_command);
}
