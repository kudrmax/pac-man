#pragma once

#include "state.h"
#include <memory>

struct IStateManager {
    virtual void set_next_state(std::unique_ptr<IState> state) = 0;
    virtual ~IStateManager() = default;
};