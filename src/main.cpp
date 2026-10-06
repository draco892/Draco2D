#include "Application/Application.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
    // Amo il mio gechino <3

    if (argc > 2) {
        std::cerr << "Usage: Draco2D [path/to/config.json]\n";
        return 1;
    }
    try {
        std::filesystem::path path = argc == 2 ? argv[1] : "Draco2DConfig.json";
        if (argc == 1 && !std::filesystem::exists(path)) {
            if (const char* base = SDL_GetBasePath()) path = std::filesystem::path(base) / path;
        }
        ConfigManager config(path);
        if (!config.isValid()) {
            std::cerr << "Configuration error: " << config.getLastErrorMessage() << '\n';
            return static_cast<int>(config.getLastError());
        }
        Application app(config.settings());
        return app.run();
    } catch (const std::exception& error) {
        std::cerr << "Draco2D: " << error.what() << '\n';
        return 1;
    }
}
