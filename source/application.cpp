#include "application.h"

int Application::run() {
    try {
        while (m_ptr_state_current->do_step()) {
//            std::cout << "do_step returns TRUE\n";
            apply_deffer_state_change();
        }
        std::cout << "do_step returns FALSE\n";
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
