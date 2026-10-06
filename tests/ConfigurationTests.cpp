#include "Application/Application.hpp"
#include "Objects/Triangle.hpp"
#include "Objects/Square.hpp"
#include "Window/ConfigWindow.hpp"
#include <array>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
void check(bool condition, const std::string& message)
{
    if (!condition) throw std::runtime_error(message);
}
bool near(float a, float b) { return std::abs(a - b) < 0.001f; }
std::string read(const std::filesystem::path& path)
{
    std::ifstream file(path);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}
struct TemporaryDirectory
{
    std::filesystem::path path = std::filesystem::temp_directory_path() /
        ("draco2d-test-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    TemporaryDirectory() { std::filesystem::create_directory(path); }
    ~TemporaryDirectory() { std::filesystem::remove_all(path); }
};
void invalid(const nlohmann::json& j, const std::string& path)
{
    try { ConfigManager::Parse(j); }
    catch (const std::exception& error) {
        check(std::string(error.what()).find(path) != std::string::npos,
              "Error must identify field: " + path + " (got " + error.what() + ")");
        return;
    }
    throw std::runtime_error("Invalid field accepted: " + path);
}
}

int main(int argc, char* argv[])
{
    try {
        check(argc == 2, "Expected sample config path");
        TemporaryDirectory temporary;
        const auto path = temporary.path / "config.json";
        const auto write = [&](const std::string& text) { std::ofstream(path) << text; };
        const std::string source = read(argv[1]);
        write(source);
        {
            ConfigManager sample(path);
            check(sample.isValid(), sample.getLastErrorMessage());
            check(sample.settings().window.width == 1280, "Sample width");
            ConfigWindow facade(path.string());
            check(facade.IsValid() && facade.GetWindowSettings().height == 720, "Window config facade");
        }
        check(read(path) == source, "Reading configuration must never change its contents");
        {
            BaseFile file(path, BaseFile::FileAccessMode::READ_WRITE);
            check(file.IsValid(), "Read/write access");
        }
        check(read(path) == source, "Read/write opening must not truncate contents");
        {
            BaseFile file(temporary.path / "new.txt", BaseFile::FileAccessMode::WRITE);
            check(file.IsValid(), "Write mode must create a file");
            *file.GetWriteFile() << "test";
        }
        check(read(temporary.path / "new.txt") == "test", "Write content");
        ConfigManager missing(temporary.path / "missing.json");
        check(!missing.isValid() && !std::filesystem::exists(temporary.path / "missing.json"), "Missing file must not be created");
        for (const auto* bad : {"", "{broken", "null", "[]"}) {
            write(bad);
            ConfigManager config(path);
            check(!config.isValid(), "Invalid JSON must fail safely");
            check(read(path) == bad, "Invalid input must not be modified");
        }
        write("{}");
        ConfigManager defaults(path);
        check(defaults.isValid() && defaults.settings().input.up == SDL_SCANCODE_UP, "Omitted fields keep defaults");
        const auto legacy = ConfigManager::Parse({{"GraphicsSettings", {{"default_color_r", 42}}}});
        check(legacy.graphics.background.r == 42 && legacy.graphics.background.b == 24, "Legacy color fields");
        invalid({{"WindowSettings", {{"width", 0}}}}, "WindowSettings.width");
        invalid({{"WindowSettings", {{"width", 3.5}}}}, "WindowSettings.width");
        invalid({{"WindowSettings", {{"height", "720"}}}}, "WindowSettings.height");
        invalid({{"WindowSettings", {{"flags", "TYPO"}}}}, "WindowSettings.flags");
        invalid({{"GraphicsSettings", {{"vsync", 1}}}}, "GraphicsSettings.vsync");
        invalid({{"GraphicsSettings", {{"default_color_r", 256}}}}, "GraphicsSettings.default_color_r");
        invalid({{"ApplicationSettings", {{"max_fps", 0}}}}, "ApplicationSettings.max_fps");
        invalid({{"InputSettings", {{"up", "not-a-key"}}}}, "InputSettings.up");
        invalid({{"InputSettings", {{"up", "Down"}}}}, "InputSettings");
        invalid({{"Objects", {{"square", {{"size", -1}}}}}}, "Objects.square.size");
        invalid({{"Objects", {{"triangle", {{"speed", -1}}}}}}, "Objects.triangle.speed");
        invalid({{"Objects", {{"rectangle", {{"color", {{"a", -1}}}}}}}}, "Objects.rectangle.color.a");
        invalid({{"Objects", {{"square", {{"colour", "red"}}}}}}, "Objects.square.colour");
        invalid({{"WindowSettings", nullptr}}, "WindowSettings");
        invalid({{"typo", true}}, "typo");

        const auto custom = ConfigManager::Parse(nlohmann::json::parse(R"({
          "WindowSettings": {"width":640,"height":480,"title":"Custom","flags":"NONE"},
          "GraphicsSettings": {"vsync":false,"default_color_r":30,"default_color_g":40,"default_color_b":50},
          "InputSettings": {"up":"W","down":"S","left":"A","right":"D","quit":"Q"},
          "Objects": {
            "triangle":{"x":10,"y":20,"width":40,"height":30,"speed":80,"color":{"r":11,"g":22,"b":33,"a":128}},
            "square":{"x":0,"y":0,"size":20,"vx":100,"vy":0,"color":{"r":44,"g":55,"b":66}},
            "rectangle":{"x":1,"y":2,"width":30,"height":40,"vx":-60,"vy":90}
          }
        })"));
        check(custom.window.width == 640 && custom.window.flags == 0 && !custom.graphics.vsync,
              "Custom window and renderer settings");
        check(custom.rectangle.bounds.w == 30 && custom.rectangle.vx == -60, "Rectangle settings");
        std::array<bool, SDL_SCANCODE_COUNT> keyboard{};
        Triangle player(custom.triangle, custom.input);
        keyboard[SDL_SCANCODE_RIGHT] = true;
        player.update({0.25f, 640, 480, keyboard.data()});
        check(near(player.bounds().x, 10), "Old arrow binding must no longer move player");
        keyboard[SDL_SCANCODE_D] = true;
        player.update({0.25f, 640, 480, keyboard.data()});
        check(near(player.bounds().x, 30), "Configured D binding and speed");
        keyboard[SDL_SCANCODE_S] = true;
        const auto before = player.bounds();
        player.update({0.25f, 640, 480, keyboard.data()});
        check(near(std::hypot(player.bounds().x - before.x, player.bounds().y - before.y), 20), "Diagonal movement must preserve speed");
        player.update({1, 50, 40, keyboard.data()});
        check(near(player.bounds().x, 10) && near(player.bounds().y, 10), "Resize-aware player boundaries");
        player.update({1, 10, 10, keyboard.data()});
        check(player.bounds().x == 0 && player.bounds().y == 0, "Oversized player pins to origin");
        Square square(custom.square), subdivided(custom.square);
        square.update({1, 100, 100, nullptr});
        for (int n = 0; n < 10; ++n) subdivided.update({0.1f, 100, 100, nullptr});
        check(near(square.bounds().x, 60) && near(square.bounds().x, subdivided.bounds().x), "Bounce must preserve overshoot and be time based");
        square.update({0.1f, 100, 100, nullptr});
        check(near(square.bounds().x, 50), "Bounced square must continue in reverse");
        square.update({1, 10, 10, nullptr});
        check(square.bounds().x == 0, "Small windows handle oversized square");

        check(SDL_Init(SDL_INIT_VIDEO), SDL_GetError());
        auto* surface = SDL_CreateSurface(100, 100, SDL_PIXELFORMAT_RGBA32);
        check(surface != nullptr, SDL_GetError());
        auto* renderer = SDL_CreateSoftwareRenderer(surface);
        check(renderer != nullptr, SDL_GetError());
        player.render(renderer);
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        check(r == 11 && g == 22 && b == 33 && a == 128, "Player RGBA reaches renderer");
        square.render(renderer);
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        check(r == 44 && g == 55 && b == 66, "Square RGB reaches renderer");
        SDL_DestroyRenderer(renderer);
        SDL_DestroySurface(surface);
        SDL_Quit();
        {
            Application app(custom);
            check(app.getLastError() == ErrorClass::Errors::DRACO2D_NO_ERROR, "Application initialization");
            int count = 0;
            auto** windows = SDL_GetWindows(&count);
            check(windows != nullptr && count == 1, "Exactly one configured window");
            int width = 0, height = 0;
            SDL_GetWindowSize(windows[0], &width, &height);
            check(width == 640 && height == 480 && std::string(SDL_GetWindowTitle(windows[0])) == "Custom",
                  "JSON dimensions and title must reach the SDL window");
            check((SDL_GetWindowFlags(windows[0]) & SDL_WINDOW_RESIZABLE) == 0, "Window flags applied");
            SDL_BlendMode blend;
            SDL_GetRenderDrawBlendMode(SDL_GetRenderer(windows[0]), &blend);
            check(blend == SDL_BLENDMODE_BLEND, "Object alpha blending enabled");
            SDL_free(windows);
            SDL_Event quit{};
            quit.type = SDL_EVENT_KEY_DOWN;
            quit.key.scancode = custom.input.quit;
            check(SDL_PushEvent(&quit), "Queue configured quit key");
            check(app.run() == 0, "Configured quit key must exit cleanly");
        }
        check(SDL_WasInit(SDL_INIT_VIDEO) == 0, "Application must release SDL");
        std::cout << "Configuration, file safety, movement, rendering, and application lifecycle checks passed.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
