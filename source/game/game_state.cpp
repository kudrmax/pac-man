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
            }
            else {
                process_key_pressed(event.key.code);
            }
        }
    }
}


void GameState::update() {
    using namespace std::chrono_literals;
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

    // display
    m_window.display();
}

void GameState::process_key_pressed(sf::Keyboard::Key key) {
    if (m_context_manager.get_context().state == GameContext::INGAME) {
        auto& new_pacman = m_context_manager.get_context().pacman;
        if (key == sf::Keyboard::A) {
            m_context_manager.save_current_context();
            new_pacman.move(Room::Direction::LEFT);
        }
        if (key == sf::Keyboard::W) {
            m_context_manager.save_current_context();
            new_pacman.move(Room::Direction::UP);
        }
        if (key == sf::Keyboard::D) {
            m_context_manager.save_current_context();
            new_pacman.move(Room::Direction::RIGHT);
        }
        if (key == sf::Keyboard::S) {
            m_context_manager.save_current_context();
            new_pacman.move(Room::Direction::DOWN);
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
};
