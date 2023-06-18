#include "select_level_state.h"
#include "../i_state_manager.h"
#include "../exit/exite_state.h"
#include "../config.h"


void SelectState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            m_state_manager.set_next_state(std::make_unique<ExitState>(m_state_manager));
            break;
        }
        auto coord_mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        auto is_pressed = event.type == sf::Event::MouseButtonPressed;
        m_menu.process_mouse(coord_mouse, is_pressed);
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
        IState(state_manager) {}

void SelectState::update() {};

void SelectState::render() {
    m_window.clear(config::SELECT_LEVEL_BACKGROUND_COLOR);
    m_menu.draw_into(m_window);
    m_window.display();
};