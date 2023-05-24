#include "application.h"

int Application::run() {
    try {
        while (m_ptr_state_current->do_step()) {
            apply_deffer_state_change();
            std::cout << "Game is worknig\n";
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
