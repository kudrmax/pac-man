#include "menu.h"
#include "../config.h"
#include "button_command.h"


void Menu::process_mouse(const sf::Vector2f& position, bool is_pressed) {
    for (auto& button: m_buttons) {
        if (button->is_position_in(position))
            button->select();
        else
            button->unselect();
        if (is_pressed && button->is_selected())
            button->push();
    }
}

Menu::Menu(IStateManager& state_manager) {
    float start_position_buttons = 100;
    float delta_position_buttons = config::BUTTON_SIZE.y + 25;

    m_buttons.emplace_back(std::make_unique<Button>(
            sf::Vector2f{ config::SELECT_LEVEL_VIDEO_MODE_WIDTH / 2, start_position_buttons },
            config::BUTTON_SIZE,
            config::BUTTON_TEXT_EASY,
            config::BUTTON_FONT_SIZE,
            std::move(std::make_unique<GameCommand>(
                    state_manager, std::make_unique<GameBuilderDirector>(
                            std::make_unique<SimpleGameBuilder>(
                                    config::SELECT_LEVEL_VIDEO_MODE_WIDTH,
                                    config::SELECT_LEVEL_VIDEO_MODE_HEIGHT,
                                    config::ROOM_SIZE),
                            config::EASY_GAME_TITLE,
                            0
                    )
            ))
    ));

    m_buttons.emplace_back(std::make_unique<Button>(
            sf::Vector2f{ config::SELECT_LEVEL_VIDEO_MODE_WIDTH / 2,
                          start_position_buttons + delta_position_buttons * 1 },
            config::BUTTON_SIZE,
            config::BUTTON_TEXT_MEDIUM,
            config::BUTTON_FONT_SIZE,
            std::move(std::make_unique<GameCommand>(
                    state_manager, std::make_unique<GameBuilderDirector>(
                            std::make_unique<SimpleGameBuilder>(
                                    config::SELECT_LEVEL_VIDEO_MODE_WIDTH,
                                    config::SELECT_LEVEL_VIDEO_MODE_HEIGHT,
                                    config::ROOM_SIZE),
                            config::MEDIUM_GAME_TITLE,
                            0
                    )
            ))
    ));

    m_buttons.emplace_back(std::make_unique<Button>(
            sf::Vector2f{ config::SELECT_LEVEL_VIDEO_MODE_WIDTH / 2,
                          start_position_buttons + delta_position_buttons * 2 },
            config::BUTTON_SIZE,
            config::BUTTON_TEXT_HARD,
            config::BUTTON_FONT_SIZE,
            std::move(std::make_unique<GameCommand>(
                    state_manager, std::make_unique<GameBuilderDirector>(
                            std::make_unique<SimpleGameBuilder>(
                                    config::SELECT_LEVEL_VIDEO_MODE_WIDTH,
                                    config::SELECT_LEVEL_VIDEO_MODE_HEIGHT,
                                    config::ROOM_SIZE),
                            config::HARD_GAME_TITLE,
                            0
                    )
            ))
    ));

    m_buttons.emplace_back(std::make_unique<Button>(
            sf::Vector2f{ config::SELECT_LEVEL_VIDEO_MODE_WIDTH / 2,
                          start_position_buttons + delta_position_buttons * 3 },
            config::BUTTON_SIZE,
            config::BUTTON_TEXT_EXIT,
            config::BUTTON_FONT_SIZE,
            std::move(std::make_unique<ExitCommand>(state_manager)))
    );
}

void Menu::draw_into(sf::RenderWindow& window) {
    for (auto& ptr_button: m_buttons)
        ptr_button->draw_into(window);
}