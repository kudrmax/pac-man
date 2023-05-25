#pragma once

#include "menu.h"
#include "state.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>
#include <memory>

//class Application : public IStateManager, std::enable_shared_from_this<Application> {
class Application : public IStateManager {
public:
//    Application() : m_ptr_state_current() {
//        m_ptr_state_current = std::make_unique<SelectState>(this, "this");
//    }
    Application() {
        std::shared_ptr<Application> obj(this);
        m_ptr_state_current = std::make_shared<SelectState>(obj,"Title");
    }
//    Application() = default;
    void set_next_state(std::shared_ptr<IState> state) override;
    int run();
    void apply_deffer_state_change() {
        if (m_ptr_state_next) {
            m_ptr_state_current = m_ptr_state_next;
            m_ptr_state_next = nullptr;
        }
//        this->set_next_state(std::move(m_ptr_state_current));
    };
private:
    std::shared_ptr<IState> m_ptr_state_current = nullptr;
    std::shared_ptr<IState> m_ptr_state_next = nullptr;
//    std::unique_ptr<IState> m_ptr_state_next{ std::make_unique<SelectState>(this, "Some title") };
};