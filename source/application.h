#pragma once

#include "i_state.h"
#include "i_state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class IState;
class ISelectCommand;

class Application : public IStateManager {
public:
    Application();
    void set_next_state(std::unique_ptr<IState>&& state) override;
    int run();
    void apply_deffer_state_change();
private:
    std::unique_ptr<IState> m_ptr_state_current = nullptr;
    std::unique_ptr<IState> m_ptr_state_next = nullptr;
};