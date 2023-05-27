#include "application.h"
#include "i_state.h"
#include "select_level/button_command.h"
#include "select_level/select_level_state.h"

int Application::run() {
    try {
        while (m_ptr_state_current->do_step()) {
            apply_deffer_state_change();
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cout << "Unknown exception\n";
        return 2;
    }
    return 0;
}

void Application::set_next_state(std::unique_ptr<IState> state) {
    m_ptr_state_next = std::move(state);
};

void Application::apply_deffer_state_change() {
    if (m_ptr_state_next) {
        m_ptr_state_current = std::move(m_ptr_state_next);
        m_ptr_state_next = nullptr;
    }
};

Application::Application() {
    m_ptr_state_current = std::make_unique<SelectState>(*this, "Title");
}
