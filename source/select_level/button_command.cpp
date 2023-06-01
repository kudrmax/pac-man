#include "button_command.h"
#include "../game/game_state.h"
#include "../exit/exite_state.h"
#include "../i_state_manager.h"


void ExitCommand::execute() {
    m_state_manager->set_next_state(std::make_unique<ExitState>(m_state_manager));
};

void GameCommand::execute() {
//    m_state_manager->set_next_state(std::make_unique<GameState>(m_state_manager, "Game"));
    auto state = m_ptr_director->build(m_state_manager);
    m_state_manager->set_next_state(std::move(state));
}
