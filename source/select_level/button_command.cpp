#include "button_command.h"
#include "../exit/exite_state.h"
#include "../i_state_manager.h"


void ExitCommand::execute() {
    m_state_manager.set_next_state(std::make_unique<ExitState>(m_state_manager));
};

void GameCommand::execute() {
    auto state = m_ptr_director->build(m_state_manager);
    m_state_manager.set_next_state(std::move(state));
}
