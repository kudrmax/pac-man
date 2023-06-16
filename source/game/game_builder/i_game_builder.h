#pragma once

#include "../game_state.h"
#include "../side.h"

struct IGameBuilder {
    virtual void create_rooms() = 0;
    virtual void set_rooms_sides() = 0;
    virtual void create_context(float dynamic_objects_ratio) = 0;
    virtual void create_state(IStateManager& state_manager, std::string window_title) = 0;
    virtual void set_all_to_state() = 0;
    virtual std::unique_ptr<GameState> get_game() = 0;
    virtual ~IGameBuilder() = default;
};