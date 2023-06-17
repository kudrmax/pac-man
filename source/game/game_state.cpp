#include "game_state.h"
#include "../i_state_manager.h"
#include "../select_level/select_level_state.h"
#include "entity.h"
#include "../exit/exite_state.h"
#include "../config.h"
#include <thread>

GameState::GameState(IStateManager& state_manager, const std::string& window_title, const sf::VideoMode& mode) :
        IWindowKeeper(mode, window_title),
        IState(state_manager) {
}

void GameState::set_context(GameContext&& context) {
    m_context_manager.set_context(std::move(context));
    m_context_manager.save_current_context();
}

bool GameState::do_step() {
    std::cout << "GameState::do_step()" << std::endl;
    event_handling();
    update();
    render();
    return true;
}

void GameState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            m_state_manager.set_next_state(std::make_unique<SelectState>(m_state_manager, config::SELECT_LEVEL_TITLE));
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                m_context_manager.restore_previous_context();
            } else
                process_key_pressed(event.key.code);
        }
    }
}


void GameState::update() {
    std::cout << "GameState::update()" << std::endl;
    if (m_context_manager.get_context()->state == GameContext::INGAME) {
        using namespace std::chrono_literals;
        auto& static_objects = m_context_manager.get_context()->static_objects;
        auto& dynamic_objects = m_context_manager.get_context()->dynamic_objects;
        auto* pacman = &m_context_manager.get_context()->pacman;

        // Pacman and food
        auto find_food = [&pacman](const auto& el) { return pacman->get_location() == el->get_location(); };
        auto food = std::find_if(static_objects.begin(), static_objects.end(), find_food);
        if (food != static_objects.end())
            (*food)->accept(pacman)->handle(m_context_manager.get_context());

        // Pacman wins
        if (static_objects.empty())
            m_context_manager.get_context()->state = GameContext::WIN;

        // Pacman and enemy
        auto find_enemy = [&pacman](const auto& el) { return pacman->get_location() == el->get_location(); };
        auto enemy = std::find_if(dynamic_objects.begin(), dynamic_objects.end(), find_enemy);
        if (enemy != dynamic_objects.end())
            (*enemy)->accept(pacman)->handle(m_context_manager.get_context());

        // Move enemy
        for (auto& enemy_for_action: dynamic_objects) {
            enemy_for_action->action();
        }
    }
};

void GameState::render() {
    m_window.clear();

    // Background
    clear_background();

    // Maze
    m_maze.draw_into(m_window);

    // static_objects
    for (auto& el: m_context_manager.get_context()->static_objects)
        el->draw_into(m_window);

    // dynamic_objects
    for (auto& el: m_context_manager.get_context()->dynamic_objects)
        el->draw_into(m_window);

    // PacMan
    m_context_manager.get_context()->pacman.draw_into(m_window);

    m_window.display();
}

void GameState::process_key_pressed(sf::Keyboard::Key key) {
    if (m_context_manager.get_context()->state == GameContext::INGAME) {
        auto& new_pacman = m_context_manager.get_context()->pacman;
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
    auto state = m_context_manager.get_context()->state;
    sf::Color background_color;
    if (state == GameContext::LOST)
        background_color = config::GAME_COLOR_BACKGROUND_LOST;
    else if (state == GameContext::WIN)
        background_color = config::GAME_COLOR_BACKGROUND_WIN;
    else
        background_color = config::GAME_COLOR_BACKGROUND_INGAME;
    m_window.clear(background_color);
};
