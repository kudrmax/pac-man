#include "button_command.h"
#include "../game/game_state.h"
#include "../exit/exite_state.h"
#include "../i_state_manager.h"


void ExitCommand::execute() {
    m_state_manager->set_next_state(std::make_unique<ExitState>(m_state_manager));
};

void GameCommand::execute() {
    std::string str = "Game";
    auto test2 = GameState(*m_state_manager, str);
    m_state_manager->set_next_state(std::make_unique<GameState>(*m_state_manager, "Game"));
};