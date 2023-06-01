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
    void set_next_state(std::unique_ptr<IState> state) override;
    int run();
    void apply_deffer_state_change();
    void call() override {
        if(!m_ptr_state_current)
            std::cout << "nullptr 1" << std::endl;
        else
            m_ptr_state_current->call();
        if(!m_ptr_state_next)
            std::cout << "nullptr 2" << std::endl;
        else
            m_ptr_state_next->call();
    };
private: // вернуть private
    std::unique_ptr<IState> m_ptr_state_current = nullptr;
    std::unique_ptr<IState> m_ptr_state_next = nullptr;
};