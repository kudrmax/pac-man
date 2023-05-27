#include "menu.h"
#include "../config.h"
#include "../select_level/button_command.h"


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