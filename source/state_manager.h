#pragma once

#include "state.h"

class IState;

struct IStateManager {
//    virtual void set_next_state(IState* state);
    virtual void set_next_state(IState* state) = 0;
    virtual ~IStateManager() = default;
};