#include "Configuration/ConfigManager.hpp"

#include <cmath>
#include <set>
#include <stdexcept>

namespace {
using Json = nlohmann::json;

void keys(const Json& value, const std::string& path,
          std::initializer_list<const char*> allowed)
{
    if (!value.is_object()) throw std::runtime_error(path + ": expected an object");
    for (const auto& [key, unused] : value.items()) {
        bool found = false;
        for (const auto* name : allowed) if (key == name) found = true;
        if (!found) throw std::runtime_error(path + "." + key + ": unknown field");
    }
}

float number(const Json& j, const char* key, float fallback, const std::string& path,
             float minimum, float maximum)
{
    if (!j.contains(key)) return fallback;
    const auto& value = j.at(key);
    if (!value.is_number()) throw std::runtime_error(path + "." + key + ": expected a number");
    const double n = value.get<double>();
    if (!std::isfinite(n) || n < minimum || n > maximum)
        throw std::runtime_error(path + "." + key + ": out of range [" +
                                 std::to_string(minimum) + ", " + std::to_string(maximum) + "]");
    return static_cast<float>(n);
}

int integer(const Json& j, const char* key, int fallback, const std::string& path,
            int minimum, int maximum)
{
    if (j.contains(key) && !j.at(key).is_number_integer())
        throw std::runtime_error(path + "." + key + ": expected an integer");
    return static_cast<int>(number(j, key, static_cast<float>(fallback), path,
                                   static_cast<float>(minimum), static_cast<float>(maximum)));
}

std::string string(const Json& j, const char* key, const std::string& fallback,
                   const std::string& path)
{
    if (!j.contains(key)) return fallback;
    if (!j.at(key).is_string() || j.at(key).get_ref<const std::string&>().empty())
        throw std::runtime_error(path + "." + key + ": expected a non-empty string");
    return j.at(key).get<std::string>();
}

SDL_Color color(const Json& j, SDL_Color fallback, const std::string& path)
{
    keys(j, path, {"r", "g", "b", "a"});
    return {static_cast<Uint8>(integer(j, "r", fallback.r, path, 0, 255)),
            static_cast<Uint8>(integer(j, "g", fallback.g, path, 0, 255)),
            static_cast<Uint8>(integer(j, "b", fallback.b, path, 0, 255)),
            static_cast<Uint8>(integer(j, "a", fallback.a, path, 0, 255))};
}

void geometry(const Json& j, SDL_FRect& rect, SDL_Color& tint,
              const std::string& path, bool square)
{
    rect.x = number(j, "x", rect.x, path, 0, 32768);
    rect.y = number(j, "y", rect.y, path, 0, 32768);
    if (square) {
        rect.w = rect.h = number(j, "size", rect.w, path, 1, 32768);
    } else {
        rect.w = number(j, "width", rect.w, path, 1, 32768);
        rect.h = number(j, "height", rect.h, path, 1, 32768);
    }
    if (j.contains("color")) tint = color(j.at("color"), tint, path + ".color");
}
}

ConfigManager::ConfigManager(const std::filesystem::path& filepath)
    : BaseConfiguration(filepath)
{
    if (IsValid()) load();
}

ErrorClass::Errors ConfigManager::load()
{
    if (!IsValid()) return getLastError();
    try {
        _settings = Parse(*GetParsedJson());
        setLastError(Errors::DRACO2D_NO_ERROR);
    } catch (const std::exception& error) {
        setIsValid(false);
        setLastError(Errors::DRACO2D_CONFIG_BAD_PARAMETERS);
        setLastCustomErrorMessage(GetFilePath().string() + ": " + error.what());
    }
    return getLastError();
}

EngineConfig ConfigManager::Parse(const Json& json)
{
    EngineConfig result;
    keys(json, "$", {"WindowSettings", "GraphicsSettings", "ApplicationSettings", "InputSettings", "Objects"});
    if (json.contains("WindowSettings")) {
        const auto& j = json.at("WindowSettings");
        const std::string p = "WindowSettings";
        keys(j, p, {"title", "width", "height", "flags"});
        result.window.title = string(j, "title", result.window.title, p);
        result.window.width = integer(j, "width", result.window.width, p, 1, 32768);
        result.window.height = integer(j, "height", result.window.height, p, 1, 32768);
        const auto flag = string(j, "flags", "RESIZABLE", p);
        if (flag == "RESIZABLE") result.window.flags = SDL_WINDOW_RESIZABLE;
        else if (flag == "NONE") result.window.flags = 0;
        else if (flag == "BORDERLESS") result.window.flags = SDL_WINDOW_BORDERLESS;
        else if (flag == "FULLSCREEN") result.window.flags = SDL_WINDOW_FULLSCREEN;
        else throw std::runtime_error(p + ".flags: expected NONE, RESIZABLE, BORDERLESS or FULLSCREEN");
    }
    if (json.contains("GraphicsSettings")) {
        const auto& j = json.at("GraphicsSettings");
        const std::string p = "GraphicsSettings";
        keys(j, p, {"vsync", "default_color_r", "default_color_g", "default_color_b", "default_color_a"});
        if (j.contains("vsync")) {
            if (!j.at("vsync").is_boolean()) throw std::runtime_error(p + ".vsync: expected a boolean");
            result.graphics.vsync = j.at("vsync").get<bool>();
        }
        auto& c = result.graphics.background;
        c.r = static_cast<Uint8>(integer(j, "default_color_r", c.r, p, 0, 255));
        c.g = static_cast<Uint8>(integer(j, "default_color_g", c.g, p, 0, 255));
        c.b = static_cast<Uint8>(integer(j, "default_color_b", c.b, p, 0, 255));
        c.a = static_cast<Uint8>(integer(j, "default_color_a", c.a, p, 0, 255));
    }
    if (json.contains("ApplicationSettings")) {
        const auto& j = json.at("ApplicationSettings");
        keys(j, "ApplicationSettings", {"max_fps"});
        result.application.maxFps = integer(j, "max_fps", result.application.maxFps,
                                            "ApplicationSettings", 1, 1000);
    }
    if (json.contains("InputSettings")) {
        const auto& j = json.at("InputSettings");
        keys(j, "InputSettings", {"up", "down", "left", "right", "quit"});
        const auto binding = [&](const char* name, SDL_Scancode fallback) {
            if (!j.contains(name)) return fallback;
            const auto text = string(j, name, "", "InputSettings");
            const auto code = SDL_GetScancodeFromName(text.c_str());
            if (code == SDL_SCANCODE_UNKNOWN)
                throw std::runtime_error(std::string("InputSettings.") + name + ": unknown key '" + text + "'");
            return code;
        };
        result.input.up = binding("up", result.input.up);
        result.input.down = binding("down", result.input.down);
        result.input.left = binding("left", result.input.left);
        result.input.right = binding("right", result.input.right);
        result.input.quit = binding("quit", result.input.quit);
    }
    const auto& i = result.input;
    if (std::set<SDL_Scancode>{i.up, i.down, i.left, i.right, i.quit}.size() != 5)
        throw std::runtime_error("InputSettings: each action must use a different key");

    if (json.contains("Objects")) {
        const auto& objects = json.at("Objects");
        keys(objects, "Objects", {"triangle", "square", "rectangle"});
        if (objects.contains("triangle")) {
            const auto& j = objects.at("triangle");
            const std::string p = "Objects.triangle";
            keys(j, p, {"x", "y", "width", "height", "color", "speed"});
            geometry(j, result.triangle.bounds, result.triangle.color, p, false);
            result.triangle.speed = number(j, "speed", result.triangle.speed, p, 0, 10000);
        }
        for (const auto* name : {"square", "rectangle"}) {
            if (!objects.contains(name)) continue;
            const auto& j = objects.at(name);
            const std::string p = std::string("Objects.") + name;
            const bool square = std::string(name) == "square";
            if (square) keys(j, p, {"x", "y", "size", "color", "vx", "vy"});
            else keys(j, p, {"x", "y", "width", "height", "color", "vx", "vy"});
            auto& object = square ? result.square : result.rectangle;
            geometry(j, object.bounds, object.color, p, square);
            object.vx = number(j, "vx", object.vx, p, -10000, 10000);
            object.vy = number(j, "vy", object.vy, p, -10000, 10000);
        }
    }
    return result;
}
