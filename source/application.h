#pragma once

#include "menu.h"
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Application : public IStateManager {
public:
    Application() {
        std::shared_ptr<Application> obj(this);
        std::cout << "obj.use_count() = " << obj.use_count() << std::endl;
        m_ptr_state_current = std::make_shared<SelectState>(obj,"Title");
        std::cout << "&*obj = " << &*obj << std::endl;
        std::cout << "obj.use_count() = " << obj.use_count() << std::endl;
    }
    void set_next_state(std::shared_ptr<IState> state) override;
    int run();
    void apply_deffer_state_change() {
        if (m_ptr_state_next) {
            m_ptr_state_current = std::move(m_ptr_state_next);
            m_ptr_state_next = nullptr;
            std::cout << "apply_deffer_state_change was applied\n";
        }
    };
private:
    std::shared_ptr<IState> m_ptr_state_current = nullptr;
    std::shared_ptr<IState> m_ptr_state_next = nullptr;
};