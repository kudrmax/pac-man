#pragma once

#include "menu.h"
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
    Application() {
        SelectState* select_state = new SelectState(this, "this");
//        m_ptr_state_current = select_state;
    }
    void set_next_state(IState* state) override {};
    int run();
    void apply_deffer_state_change() {};
private:
    void event_handling() {};
    void update() {};
    void render() {};
private:
    IState* m_ptr_state_current = nullptr;
    IState* m_ptr_state_next = nullptr;
};