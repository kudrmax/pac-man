#pragma once

#include "menu.h"
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
//    Application() {
//        m_ptr_state_current = std::make_unique<SelectState>(*this,"Title");
//    }
    void set_next_state(std::unique_ptr<IState> state) override;
    int run();
    void apply_deffer_state_change() {
        if (m_ptr_state_next) {
            m_ptr_state_current = std::move(m_ptr_state_next);
            m_ptr_state_next = nullptr;
            std::cout << "apply_deffer_state_change was applied\n";
        }
    };
private:
    std::unique_ptr<IState> m_ptr_state_current{ std::make_unique<SelectState>(*this, "Title") };
    std::unique_ptr<IState> m_ptr_state_next = nullptr;
//    IState* m_ptr_state_next = nullptr;
};