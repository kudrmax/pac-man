#include "state.h"
#include "config.h"
#include <iostream>

void Button::draw_into(sf::RenderWindow& window) {
    window.draw(m_rectangle);
    window.draw(m_text);
//    window.display();
//    std::cout << "draw_into() in Button\n";
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
    sf::Vector2f position(config::SELECT_LEVEL_VIDEO_MODE.width, config::SELECT_LEVEL_VIDEO_MODE.height);
    std::cout << "position: " << position.x << " " << position.y << std::endl;
    auto start_position = 100;
    auto height_button = config::BUTTON_SIZE.y;
    auto delta_position = 20;
    position.x /= 2;
    position.y = start_position;
    size_t n = 4;
    for (size_t i = 0; i < n; ++i) {
        position.y = start_position + i * (delta_position + height_button);
        m_buttons.push_back(std::make_unique<Button>(
                Button(position, config::BUTTON_SIZE, "Exit", config::BUTTON_FONT_SIZE, nullptr)));
    }
    std::cout << "in Menu()\n";
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
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title) {};