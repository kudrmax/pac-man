#include "application.h"

int main() {
    Application app;
    std::cout << "app = " << &app << std::endl;
    app.run();
    std::cout << "END\n";
    return 0;
}
