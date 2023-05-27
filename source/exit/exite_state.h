#pragma once

#include "../i_state.h"

class ExitState : public IState {
public:
    using IState::IState;
    bool do_step() override;
};