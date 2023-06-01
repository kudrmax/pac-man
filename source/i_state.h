#pragma once

#include "i_draw.h"

class IStateManager;

class IState {
public:
    IState(IStateManager* state_manager) : m_state_manager(state_manager) {};
    virtual bool do_step() = 0;
    virtual ~IState() = default;
    virtual void call() = 0;
protected:
    IStateManager* m_state_manager = nullptr;
};







