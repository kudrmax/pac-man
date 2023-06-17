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

        // delete food
        auto food = std::find_if(static_objects.begin(), static_objects.end(),
                                 [&](const auto& el) {
                                     return pacman->get_location() == el->get_location();
                                 });
        if (food != static_objects.end()) {
            auto food_to_delete = (*food)->accept(pacman);
            food_to_delete->handle(m_context_manager.get_context());
        }
        if (static_objects.empty()) {
            m_context_manager.get_context()->state = GameContext::WIN;
            std::cout << "YOU WIN\n";
        }
        std::cout << "GameState::update end()" << std::endl;


        // lost game if you're in entity
//        auto enemy = std::find_if(dynamic_objects.begin(), dynamic_objects.end(),
//                                  [&](const auto& el) {
//                                      return pacman->get_location() == el->get_location();
//                                  });
//        if (enemy != dynamic_objects.end()) {
//            auto enemy_to_delete = (*enemy)->accept(pacman);
//            enemy_to_delete->handle(m_context_manager.get_context());
//            std::cout << "YOU LOST here\n";
//        }
//        if (m_context_manager.get_context()->state == GameContext::LOST) {
//            std::cout << "YOU LOST\n";
//        }

        // move enemy
//        for (auto& enemy_for_action: dynamic_objects) {
//            enemy_for_action->action();
//        }
    }
};

void GameState::render() {
    std::cout << "GameState::render start()" << std::endl;
    m_window.clear();

    clear_background();

//    m_context_manager.get_context()->pacman.draw_into(m_window);

//    for (auto& el: m_context_manager.get_context()->static_objects)
//        el->draw_into(m_window);
//
//    for (auto& el: m_context_manager.get_context()->dynamic_objects)
//        el->draw_into(m_window);
    std::cout << "m_maze.draw_into(m_window); start" << std::endl;
    m_maze.draw_into(m_window);
    std::cout << "m_maze.draw_into(m_window); end" << std::endl;

//    auto tickness = 25;
//    sf::RectangleShape rec;


//    if (m_context_manager.get_context()->state == GameContext::WIN) {
//        rec.setSize({ static_cast<float>(config::GAME_VIDEO_MODE.width) - tickness * 2,
//                      static_cast<float>(config::GAME_VIDEO_MODE.height) - tickness * 2 });
//        rec.setOrigin({ rec.getSize().x / 2, rec.getSize().y / 2 });
//        rec.setPosition({ static_cast<float>(config::GAME_VIDEO_MODE.width) / 2,
//                          static_cast<float>(config::GAME_VIDEO_MODE.height) / 2 });
//        rec.setOutlineThickness(tickness);
//        rec.setOutlineColor(sf::Color::Green);
//        rec.setFillColor(sf::Color::Transparent);
//        m_window.draw(rec);
//    } else if (m_context_manager.get_context()->state == GameContext::LOST) {
////        rec.setSize({ static_cast<float>(config::GAME_VIDEO_MODE.width) - tickness * 2,
////                      static_cast<float>(config::GAME_VIDEO_MODE.height) - tickness * 2 });
////        rec.setOrigin({ rec.getSize().x / 2, rec.getSize().y / 2 });
////        rec.setPosition({ static_cast<float>(config::GAME_VIDEO_MODE.width) / 2,
////                          static_cast<float>(config::GAME_VIDEO_MODE.height) / 2 });
////        rec.setOutlineThickness(tickness);
////        rec.setOutlineColor(sf::Color::Red);
////        rec.setFillColor(sf::Color::Transparent);
//    }
//    m_window.draw(rec);

    m_window.display();
    std::cout << "GameState::render end()" << std::endl;

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
