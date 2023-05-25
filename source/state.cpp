#include "state.h"
#include <iostream>

void Button::draw_into(sf::RenderWindow& window) {
    window.clear();
    window.draw(m_rectangle);
    window.draw(m_text);
    window.display();
    std::cout << "draw_into() in Button\n";
};

Button::Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size,
               ISelectCommand* ptr_command) {
    m_rectangle.setFillColor(sf::Color::Yellow);
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
    std::cout << "I'm here\n";
};

Menu::Menu(IStateManager* state_manager) {
    m_buttons.push_back(std::make_unique<Button>(Button({ 1000, 200 }, { 400, 200 }, "Exit", 100, nullptr)));
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