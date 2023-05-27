#pragma once

#include "../state/state.h"

class ExitState : public IState {
public:
    using IState::IState;
    bool do_step() override;
};