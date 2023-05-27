#include "game_state.h"
#include "../config.h"

GameState::GameState(IStateManager& state_manager, const std::string& window_title) :
        IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title),
        IState(&state_manager) {}