#pragma once
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
    void set_next_state(IState* state) override {};
    int run();
    void apply_deffer_state_change(){};
private:
    void event_handling(){};
    void update(){};
    void render(){};
private:
    IState* m_ptr_state_current;
    IState* m_ptr_state_next;
};