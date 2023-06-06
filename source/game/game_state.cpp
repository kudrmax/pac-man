#include "game_state.h"
#include "entity.h"
#include "../exit/exite_state.h"
#include "../config.h"
#include <thread>

GameState::GameState(IStateManager* state_manager, const std::string& window_title) :
        IWindowKeeper(config::GAME_VIDEO_MODE, window_title),
        IState(state_manager) {
}

void GameState::set_context(GameContext&& context) {
    m_context_manager.set_context(std::move(context));
}

bool GameState::do_step() {
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
            m_state_manager->set_next_state(std::make_unique<ExitState>(m_state_manager));
            break;
        }
        if (event.type == sf::Event::KeyPressed)
            process_key_pressed(event.key.code);
    }
}


void GameState::update() {
    using namespace std::chrono_literals;
    auto& static_objects = m_context_manager.get_context().static_objects;
    auto* pacman = &m_context_manager.get_context().pacman;
    auto food = std::find_if(static_objects.begin(), static_objects.end(),
                             [&](auto el) {
                                 return pacman->get_location() == el->get_location();
                             });
    if (food != static_objects.end()) {
        auto food_to_delete = (*food)->accept(pacman);
        food_to_delete->handle(&m_context_manager.get_context());
    }
};

void GameState::render() {
    m_window.clear();
    m_maze->draw_into(m_window);
    m_context_manager.get_context().pacman.draw_into(m_window);
    for (auto& el: m_context_manager.get_context().static_objects)
        el->draw_into(m_window);
    m_window.display();
}
void GameState::process_key_pressed(sf::Keyboard::Key key) {
    auto new_pacman = m_context_manager.get_context();
    if (key == sf::Keyboard::A)
        new_pacman.pacman.move(Room::Direction::LEFT);
    if (key == sf::Keyboard::W)
        new_pacman.pacman.move(Room::Direction::UP);
    if (key == sf::Keyboard::D)
        new_pacman.pacman.move(Room::Direction::RIGHT);
    if (key == sf::Keyboard::S)
        new_pacman.pacman.move(Room::Direction::DOWN);
    m_context_manager.set_context(std::move(new_pacman));
};
