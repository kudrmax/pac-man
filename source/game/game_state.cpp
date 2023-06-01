#include "game_state.h"
#include "../config.h"

GameState::GameState(IStateManager& state_manager, const std::string& window_title) :
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
        IState(&state_manager) {}

void GameState::set_context(GameContext&& context) {
//    m_context_manager.set_context(std::move(context));
//    m_context_manager.save_current_context();
}
