#include "state_manager.h"
#include "draw.h"
#include "state.h"
#include "config.h"
#include <iostream>


void SelectState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            auto exit_ptr = std::make_unique<ExitState>(m_state_manager);
            m_state_manager->set_next_state(std::move(exit_ptr));
            break;
        }
        auto position_int = sf::Mouse::getPosition(m_window);
        auto position_float = m_window.mapPixelToCoords(position_int);
        m_menu.process_mouse(position_float, event.type == sf::Event::MouseButtonPressed);
    }
};

bool SelectState::do_step() {
    event_handling();
    update();
    render();
    return true;
};

//SelectState::SelectState(IStateManager* state_manager, const std::string& window_title) :
//        m_menu(std::make_shared<IStateManager>(state_manager)),
//        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
//        IState(state_manager) {}

SelectState::SelectState(IStateManager& state_manager, const std::string& window_title) :
        m_menu(state_manager),
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
        IState(&state_manager) {}

void SelectState::update() { m_menu.draw_into(m_window); };
void SelectState::render() { m_window.display(); };