#include "game_state.h"
#include "entity.h"
#include "../i_state_manager.h"
#include "../select_level/select_level_state.h"
#include "../config.h"
#include <memory>

GameState::GameState(IStateManager& state_manager, const std::string& window_title, const sf::VideoMode& mode) :
        IWindowKeeper(mode, window_title),
        IState(state_manager) {
}

void GameState::set_context(GameContext&& context) {
    m_context_manager.set_context(std::move(context));
    m_context_manager.save_current_context();
}

bool GameState::do_step() {
    sf::Event event;
    event_handling();
    if (m_context_manager.get_context().state == GameContext::INGAME && !m_do_not_update)
        update();
    render();
    return true;
}

void GameState::event_handling() {
    sf::Event event;
    m_do_not_update = false;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            m_state_manager.set_next_state(
                    std::make_unique<SelectState>(m_state_manager, config::SELECT_LEVEL_TITLE));
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.control && event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Escape) {
                m_context_manager.restore_previous_context();
                m_do_not_update = true;
            } else {
                process_key_pressed(event.key.code);
            }
        }
    }
}


void GameState::update() {
    auto& context = m_context_manager.get_context();
    auto& static_objects = context.static_objects;
    auto& dynamic_objects = context.dynamic_objects;
    auto& pacman = context.pacman;
    std::vector<std::unique_ptr<IGameEvent>> game_events;

    // dynamic_objects -- action
    for (auto& enemy_for_action: dynamic_objects)
        enemy_for_action->action();

    // PacMan and static_objects
    auto find_food = [&pacman](const auto& el) { return &pacman.get_location() == &el->get_location(); };
    auto food = std::find_if(static_objects.begin(), static_objects.end(), find_food);
    if (food != static_objects.end())
        game_events.push_back((*food)->accept(pacman));

    // Pacman wins
    if (static_objects.empty())
        game_events.push_back(std::make_unique<WinGame>());

    // Pacman and dynamic_objects
    auto find_enemy = [&pacman](const auto& el) { return &pacman.get_location() == &el->get_location(); };
    auto enemy = std::find_if(dynamic_objects.begin(), dynamic_objects.end(), find_enemy);
    if (enemy != dynamic_objects.end())
        game_events.push_back((*enemy)->accept(pacman));

    // Обработать все IGameEvent
    for (auto& event: game_events)
        process_event(std::move(event));
};

void GameState::render() {
    // Background
    clear_background();

    // Maze
    m_maze.draw_into(m_window);

    // static_objects
    for (auto& static_object: m_context_manager.get_context().static_objects)
        static_object->draw_into(m_window);

    // dynamic_objects
    for (auto& dynamic_object: m_context_manager.get_context().dynamic_objects)
        dynamic_object->draw_into(m_window);

    // PacMan
    m_context_manager.get_context().pacman.draw_into(m_window);

    effect_from_state();

    // display
    m_window.display();
}

void GameState::process_key_pressed(sf::Keyboard::Key key) {
    if (m_context_manager.get_context().state == GameContext::INGAME) {
        auto& new_pacman = m_context_manager.get_context().pacman;
        switch (key) {
            case config::KEY_LEFT:
                m_context_manager.save_current_context();
                new_pacman.move(Room::Direction::LEFT);
                break;
            case config::KEY_UP:
                m_context_manager.save_current_context();
                new_pacman.move(Room::Direction::UP);
                break;
            case config::KEY_RIGHT:
                m_context_manager.save_current_context();
                new_pacman.move(Room::Direction::RIGHT);
                break;
            case config::KEY_DOWN:
                m_context_manager.save_current_context();
                new_pacman.move(Room::Direction::DOWN);
                break;
        }
    }
}

void GameState::clear_background() {
    sf::Color background_color;
    switch (m_context_manager.get_context().state) {
        case GameContext::LOST:
            background_color = config::GAME_COLOR_BACKGROUND_LOST;
            break;
        case GameContext::WIN:
            background_color = config::GAME_COLOR_BACKGROUND_WIN;
            break;
        default:
            background_color = config::GAME_COLOR_BACKGROUND_INGAME;
            break;
    }
    m_window.clear(background_color);
}

void GameState::effect_from_state() {
    if (m_context_manager.get_context().state == GameContext::LOST) {
        sf::Font m_font;
        if (!m_font.loadFromFile(config::FONT_FILE))
            throw std::runtime_error("No such file in directory");
        sf::Text text;
        text.setFont(m_font);
        text.setString("Game Over!");
        text.setCharacterSize(config::TEXT_FOR_STATE_SIZE);
        auto textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
        text.setFillColor(config::BUTTON_COLOR_TEXT);
        text.setOutlineColor(config::BUTTON_COLOR_FRAME);
        text.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);

        auto color = sf::Color{ 255, 150, 150, 250 / 2 };
        sf::RectangleShape background;
        background.setFillColor(color);
        background.setSize({ static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y) });
        m_window.draw(background);
        m_window.draw(text);
    } else if (m_context_manager.get_context().state == GameContext::WIN) {
        sf::Font m_font;
        if (!m_font.loadFromFile(config::FONT_FILE))
            throw std::runtime_error("No such file in directory");
        sf::Text text;
        text.setFont(m_font);
        text.setString("Win!");
        text.setCharacterSize(config::TEXT_FOR_STATE_SIZE);
        auto textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
        text.setFillColor(config::BUTTON_COLOR_TEXT);
        text.setOutlineColor(config::BUTTON_COLOR_FRAME);
        text.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);

        auto color = sf::Color{ 150, 255, 150, 250 / 2 };
        sf::RectangleShape background;
        background.setFillColor(color);
        background.setSize({ static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y) });
        m_window.draw(background);
        m_window.draw(text);
    }
};
