#include <iostream>
#include "../include/Application.hpp"

int main()
{
    Application app;

    int result = app.run();
    if (result != DRACO2D_NO_ERROR) {
        std::cerr << "Application exited with error code: " << result << '\n';
    }

    return result;
}
