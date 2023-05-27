#include "draw.h"
#include "config.h"
#include "state.h"
#include <thread>

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

Menu::Menu(IStateManager& state_manager) {

    std::vector<std::pair<std::string, std::unique_ptr<IChangeStateCommand>>> buttons_vector;

    // Create buttons here
    buttons_vector.emplace_back("Easy", std::make_unique<GameCommand>(state_manager));
//    buttons_vector.emplace_back("Easy", std::make_unique<ExitCommand>(state_manager));
    buttons_vector.emplace_back("Medium", std::make_unique<ExitCommand>(state_manager));
    buttons_vector.emplace_back("Hard", std::make_unique<ExitCommand>(state_manager));
    buttons_vector.emplace_back("Exit", std::make_unique<ExitCommand>(state_manager));

    sf::Vector2f position(config::SELECT_LEVEL_VIDEO_MODE.width, config::SELECT_LEVEL_VIDEO_MODE.height);
    float start_position = 100;
    float delta_position = 20;
    float height_button = config::BUTTON_SIZE.y;
    position.x /= 2;
    position.y = start_position;
    for (size_t i = 0; i < buttons_vector.size(); ++i) {
        position.y = start_position + i * (delta_position + height_button);
        m_buttons.push_back(std::make_unique<Button>(
                Button(
                        position,
                        config::BUTTON_SIZE,
                        std::move(buttons_vector[i].first),
                        config::BUTTON_FONT_SIZE,
                        std::move(buttons_vector[i].second)))
        );
    }
}

void Menu::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_button: m_buttons)
        ptr_button->draw_into(window);
}

void Button::push() { m_ptr_command->execute(); };

void Menu::process_mouse(sf::Vector2f pos, bool is_pressed) {
    for (auto& button: m_buttons) {
        if (button->is_position_in(pos)) {
            button->select();
            if (is_pressed)
                button->push();
        } else {
            button->unselect();
        }
    }
}

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

//void Button::process_button() {
//    if (m_is_selected)
//        setFillColor(config::BUTTON_COLOR_SELECTION);
//    else
//        setFillColor(config::BUTTON_COLOR_FILL);
//}