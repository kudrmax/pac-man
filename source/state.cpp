#include "state.h"
#include "config.h"
#include <iostream>


void SelectState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            m_state_manager->set_next_state(std::make_unique<ExitState>(m_state_manager));
            break;
        }
        auto position_float = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        m_menu.process_mouse(position_float, event.type == sf::Event::MouseButtonPressed);
    }
};

bool SelectState::do_step() {
    event_handling();
    update();
    render();
    return true;
};

SelectState::SelectState(IStateManager& state_manager, const std::string& window_title) :
        m_menu(state_manager),
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
        IState(&state_manager) {}

void SelectState::update() {
    m_menu.draw_into(m_window);
};

void SelectState::render() { m_window.display(); };

void ExitCommand::execute() {
    m_state_manager->set_next_state(std::make_unique<ExitState>(m_state_manager));
};

void GameCommand::execute() {
    std::string str = "Game";
    auto test2 = GameState(*m_state_manager, str);
    m_state_manager->set_next_state(std::make_unique<GameState>(*m_state_manager, "Game"));
};

GameState::GameState(IStateManager& state_manager, const std::string& window_title) :
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
        IState(&state_manager) {}