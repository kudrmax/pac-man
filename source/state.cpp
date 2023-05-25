#include "state.h"
#include <iostream>

void Button::draw_into(sf::RenderWindow& window) {
    window.draw(m_rectangle);
    window.draw(m_text);
    window.display();
    std::cout << "draw_into() in Button\n";
};

Button::Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
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

Menu::Menu(IStateManager* state_manager) {
    m_buttons.push_back(std::make_unique<Button>(Button({ 50, 50 }, { 100, 50 }, "Exit", 100, nullptr)));
};

void Menu::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_button: m_buttons)
        ptr_button->draw_into(window);
};

void SelectState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            auto exit_ptr = std::make_unique<ExitState>();;
            return;
        }
    }
};

bool SelectState::do_step() {
    event_handling();
    update();
    render();
    return true;
};

SelectState::SelectState(IStateManager* state_manager, const std::string& window_title) :
        m_menu(state_manager),
        IWindowKeeper({ 2000, 1000 }, window_title) {};