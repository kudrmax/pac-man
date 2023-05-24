#pragma once

#include "menu.h"
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
    Application() {
        m_ptr_state_current = std::make_unique<SelectState>(this, "this");
    }
    void set_next_state(std::unique_ptr<IState> state) override {};
    int run();
    void apply_deffer_state_change() {};
private:
    void event_handling() {};
    void update() {};
    void render() {};
private:
    std::unique_ptr<IState> m_ptr_state_current = nullptr;
    std::unique_ptr<IState> m_ptr_state_next = nullptr;
};