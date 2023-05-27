#pragma once

#include "draw.h"

class IState {
public:
    IState(IStateManager* state_manager) : m_state_manager(state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
protected:
    IStateManager* m_state_manager = nullptr;
};







