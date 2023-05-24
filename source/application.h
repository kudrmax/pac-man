#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
    void set_next_state(std::unique_ptr<IState> state){};
    int run();
    void apply_deffer_state_change(){};
private:
    void event_handling(){};
    void update(){};
    void render(){};
private:
    std::unique_ptr<IState> m_ptr_state_current = std::make_unique<SelectState>();
    std::unique_ptr<IState> m_ptr_state_next;
};