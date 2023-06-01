#pragma once

#include "i_state.h"
#include <memory>

class IState;

struct IStateManager {
    virtual void set_next_state(std::unique_ptr<IState> state) = 0;
    virtual void call() = 0; // удалить
    virtual ~IStateManager() = default;
};