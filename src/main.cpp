#include <iostream>
#include "../include/Application.hpp"
#include "../include/errors.h"

int main()
{
    Application app;

    int result = app.run();
    if (result != DRACO2D_NO_ERROR) {
        std::cerr << "Application exited with error code: " << result << '\n';
    }

    return result;
}
