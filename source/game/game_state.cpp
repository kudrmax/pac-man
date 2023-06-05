#include "game_state.h"
#include "../exit/exite_state.h"
#include "../i_state_manager.h"
#include "../config.h"

GameState::GameState(IStateManager* state_manager, const std::string& window_title) :
        IWindowKeeper(config::GAME_VIDEO_MODE, window_title),
        IState(state_manager) {
//    std::vector<std::shared_ptr<Room>> vec_rooms(1);
//    m_maze = Maze(vec_rooms);
}

void GameState::set_context(GameContext&& context) {
    m_context_manager.set_context(std::move(context));
//    m_context_manager.save_current_context();
}

bool GameState::do_step() {
    event_handling();
//    std::cout << "GameState::do_step event_handling is done\n";
    update();
//    std::cout << "GameState::do_step event_handling is update\n";
    render();
//    std::cout << "GameState::do_step event_handling is render\n";
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
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                auto new_pacman = m_context_manager.get_context();
                new_pacman.pacman.move(Room::Direction::LEFT);
                m_context_manager.set_context(std::move(new_pacman));
            }
            if (event.key.code == sf::Keyboard::W) {
                auto new_pacman = m_context_manager.get_context();
                new_pacman.pacman.move(Room::Direction::UP);
                m_context_manager.set_context(std::move(new_pacman));
            }
            if (event.key.code == sf::Keyboard::D) {
                auto new_pacman = m_context_manager.get_context();
                new_pacman.pacman.move(Room::Direction::RIGHT);
                m_context_manager.set_context(std::move(new_pacman));
            }
            if (event.key.code == sf::Keyboard::S) {
                auto new_pacman = m_context_manager.get_context();
                new_pacman.pacman.move(Room::Direction::DOWN);
                m_context_manager.set_context(std::move(new_pacman));
            }
        }
//        std::cout << "GameState::event_handling is done" << std::endl;
//        auto position_float = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
//        m_menu.process_mouse(position_float, event.type == sf::Event::MouseButtonPressed);
    }
}


void GameState::update() {
//    m_context_manager.draw_into(m_window);
//    std::cout << "GameState::update is stated" << std::endl;
    m_window.clear();
    m_maze->draw_into(m_window);
//    std::cout << "here 1" << std::endl;
    auto context = m_context_manager.get_context();
//    std::cout << "here 2" << std::endl;
    context.pacman.draw_into(m_window);
//    std::cout << "here 3" << std::endl;
//    std::cout << "GameState::update is done" << std::endl;
};

void GameState::render() {
//    m_window.clear();
    m_window.display();
};
