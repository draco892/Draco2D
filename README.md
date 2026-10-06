# Draco2D

Draco2D is an educational 2D engine prototype written in **C++23**, using **SDL3** for windowing, input, and rendering. The CMake project builds the `Draco2D` demo, an internal `Draco2DCore` library, and optional tests (project version `0.1.0`).

The project explores application lifecycle management, polymorphic game objects, geometric rendering, and validated JSON configuration. Window settings, background and object colors, shape dimensions and positions, movement speeds, and player keyboard bindings can all be changed without recompiling.

## Current demo

The demo requests a resizable **1280 × 720** window titled `Draco2D Engine`, with a dark background (`18, 18, 24`) and three outline shapes:

| Object | Color | Behavior |
| --- | --- | --- |
| Triangle | Red | Moves with the arrow keys |
| Square | Green | Moves automatically and reverses velocity at the current render boundaries |
| Rectangle | Blue | Moves automatically and reverses velocity at the current render boundaries |

Close the window or press **Escape** to exit. Movement uses pixels per second, with normalized diagonal input. Boundaries follow the current render dimensions when resizing. These controls, dimensions, and colors are defaults from `Draco2DConfig.json`.

## Architecture

| Module | Responsibility |
| --- | --- |
| `Application` | Owns the window, renderer, and object collection; polls events and runs the update/render loop |
| `Window` | Wraps an `SDL_Window` handle |
| `Render` | Wraps an `SDL_Renderer` handle; the demo also calls SDL rendering functions directly |
| `Objects` | Implements `Triangle`, `Square`, and `Rectangle` through the `BaseObject` interface |
| `Base` | Provides object interfaces, color types, validation state, error codes, file streams, and a JSON configuration base class |
| `Configuration` | Validates JSON and exposes typed settings to the application and objects |

`Application` stores objects in a `std::vector<std::unique_ptr<BaseObject>>`. Each frame polls SDL events, updates objects using elapsed time and current render dimensions, clears the renderer, draws objects, and presents the frame. `max_fps` caps rendering even if VSync is unavailable. The elapsed time is capped at 50 ms per update to prevent large jumps after a pause.

```text
Draco2D/
├── CMakeLists.txt
├── Draco2DConfig.json
├── include/
│   ├── Application/
│   ├── Base/
│   ├── Configuration/
│   ├── Objects/
│   ├── Render/
│   └── Window/
├── src/
│   ├── main.cpp
│   ├── Application/
│   ├── Base/
│   ├── Configuration/
│   ├── Objects/
│   ├── Render/
│   └── Window/
├── tests/
├── notes/
├── TODO.txt
├── animation_plan.txt
└── LICENSE
```

## Requirements and dependencies

- **CMake 3.25 or newer**.
- A compiler and standard library supporting **C++23**.
- A build tool such as Ninja, Make, Xcode, or Visual Studio.
- Git and network access when CMake needs to fetch dependencies.

CMake prefers installed packages by default (`DRACO2D_PREFER_SYSTEM_DEPS=ON`), falling back to the versions below when a package is not found:

| Dependency | Purpose | FetchContent version |
| --- | --- | --- |
| SDL3 | Windowing, events, keyboard state, and 2D rendering | `release-3.2.14` |
| nlohmann/json | JSON parsing | `3.12.0` |

The system lookup requires nlohmann/json 3.12.0 or newer; SDL3 lookup does not specify a version. Neither Boost nor Qt is required.

## Build and run

Run the commands below from the repository root. Use a separate build directory for each generator or toolchain.

### macOS

With Apple's command-line developer tools and Homebrew available:

```bash
brew install cmake ninja sdl3 nlohmann-json
cmake -S . -B build-macos -G Ninja -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$(brew --prefix)"
cmake --build build-macos
./build-macos/Draco2D
```

Alternatively, with full Xcode installed:

```bash
cmake -S . -B build-xcode -G Xcode \
  -DCMAKE_PREFIX_PATH="$(brew --prefix)"
cmake --build build-xcode --config Debug
./build-xcode/Debug/Draco2D
```

### Linux

Install a C++23 toolchain, CMake, and Ninja using your distribution's package manager. Install SDL3 and nlohmann/json development packages where available, or allow CMake to fetch them. Building SDL3 from source also requires the development libraries for the platform backends you intend to use.

```bash
cmake -S . -B build-linux -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-linux
./build-linux/Draco2D
```

### Windows

Use Visual Studio 2022 with the C++ desktop workload and a Windows SDK. From a developer shell:

```powershell
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64
cmake --build build-vs --config Debug
.\build-vs\Debug\Draco2D.exe
```

For a shared SDL3 build, ensure `SDL3.dll` is available beside the executable or on `PATH`; the project does not currently copy runtime DLLs automatically.

### Dependency options

For dependencies installed outside standard search locations, pass their installation prefixes during configuration:

```bash
cmake -S . -B build-custom -DCMAKE_PREFIX_PATH="/path/to/dependency/prefix"
```

To request fetched dependencies, start with a fresh build directory:

```bash
cmake -S . -B build-fetched -DDRACO2D_PREFER_SYSTEM_DEPS=OFF
```

## JSON configuration

Edit [`Draco2DConfig.json`](Draco2DConfig.json) and restart the demo. Settings are read once at startup; there is no live reload.

With no argument, the executable first looks for `Draco2DConfig.json` in the current working directory, then beside the executable. CMake copies the repository's configuration beside the binary during a normal build. Build-time copying may overwrite edits to that copy, so edit the source file or keep a separate custom configuration.

To select a file explicitly:

```bash
./build-macos/Draco2D /path/to/my-config.json
```

An explicit relative path is resolved against the current working directory. A missing, unreadable, or invalid file prevents startup and returns a nonzero exit code. Configuration is opened read-only and is never rewritten by the application.

All sections and fields are optional: omitted values retain the defaults shown below. Unknown fields, wrong types, out-of-range values, unknown keys, and duplicate input bindings are rejected with an error identifying the field. The original `WindowSettings` and `GraphicsSettings` format remains supported.

```json
{
    "WindowSettings": {
        "title": "Draco2D Engine",
        "width": 1280,
        "height": 720,
        "flags": "RESIZABLE"
    },
    "GraphicsSettings": {
        "vsync": true,
        "default_color_r": 18,
        "default_color_g": 18,
        "default_color_b": 24,
        "default_color_a": 255
    },
    "ApplicationSettings": {
        "max_fps": 120
    },
    "InputSettings": {
        "up": "Up",
        "down": "Down",
        "left": "Left",
        "right": "Right",
        "quit": "Escape"
    },
    "Objects": {
        "triangle": {
            "x": 240,
            "y": 100,
            "width": 800,
            "height": 420,
            "color": { "r": 255, "g": 0, "b": 0, "a": 255 },
            "speed": 120
        },
        "square": {
            "x": 540,
            "y": 260,
            "size": 200,
            "color": { "r": 0, "g": 255, "b": 0, "a": 255 },
            "vx": 120,
            "vy": 120
        },
        "rectangle": {
            "x": 470,
            "y": 285,
            "width": 300,
            "height": 150,
            "color": { "r": 0, "g": 0, "b": 255, "a": 255 },
            "vx": 120,
            "vy": 120
        }
    }
}
```

| Settings | Meaning and accepted values |
| --- | --- |
| `WindowSettings.title` | Non-empty window title |
| `WindowSettings.width`, `height` | Integer window dimensions from 1 to 32768 |
| `WindowSettings.flags` | One of `NONE`, `RESIZABLE`, `BORDERLESS`, `FULLSCREEN` |
| `GraphicsSettings.vsync` | Boolean; unsupported VSync produces a warning and falls back to the FPS cap |
| `GraphicsSettings.default_color_r/g/b/a` | Background RGBA channels, each an integer from 0 to 255 |
| `ApplicationSettings.max_fps` | Integer frame cap from 1 to 1000; VSync can impose a lower limit |
| `InputSettings.up/down/left/right/quit` | SDL scancode names such as `Up`, `W`, `Space`, `Escape`, or `Left Shift`; each action needs a distinct key |
| `Objects.*.x`, `y` | Initial top-left position in render coordinates, from 0 to 32768 |
| `Objects.triangle.width/height`, `Objects.rectangle.width/height` | Dimensions from 1 to 32768; fractional values are supported |
| `Objects.square.size` | Side length from 1 to 32768 |
| `Objects.*.color.r/g/b/a` | Per-object RGBA channels, each an integer from 0 to 255; object alpha is blended over the background |
| `Objects.triangle.speed` | Player speed from 0 to 10000 pixels per second |
| `Objects.square.vx/vy`, `Objects.rectangle.vx/vy` | Signed velocity from -10000 to 10000 pixels per second; zero stops movement on that axis |

The triangle is an isosceles outline inside its configured bounding rectangle. Coordinates outside the visible bounds are clamped on the first update and after resizing. If a shape is larger than the render area, it is pinned to zero on that axis and the excess is clipped; it is not scaled down. Fullscreen dimensions may be selected by the display system. Background alpha does not make the operating-system window transparent.

For WASD movement, change just this section:

```json
"InputSettings": {
    "up": "W",
    "down": "S",
    "left": "A",
    "right": "D",
    "quit": "Escape"
}
```

Bindings refer to physical SDL scancodes rather than text input, so keyboard layout can affect the printed character on a bound key. Mouse and controller bindings are not implemented.

## Tests and current limitations

Tests are enabled by default through CTest. After building:

```bash
ctest --test-dir build-macos --output-on-failure
```

For Xcode or Visual Studio, also specify `-C Debug`. Use `-DBUILD_TESTING=OFF` at configuration time to omit the test executable.

The tests cover defaults and custom settings, invalid configuration, preservation of file contents, configurable movement keys, time-based movement and boundary handling, object draw colors, and application initialization and shutdown with the configured quit key. They run with SDL's dummy video driver, without opening a desktop window.

The Debug build and tests have been verified on macOS with AppleClang 21, Ninja, and system dependencies. Native visual interaction, Linux, Windows, and fetched-dependency builds have not been verified in this change. Rendering remains outline-only; there is no scene manager, texture loading, or collision detection between objects. Configuration is applied at startup, and movement uses a variable timestep.

## Extending the project

To add a drawable object, derive from `BaseObject`, implement `update(const UpdateContext&)` and `render(SDL_Renderer*) const`, and register an instance in `Application::Initialize()`. Add any new source files to `CMakeLists.txt`.

Further planned work includes scene/entity management, broader input handling, textures and sprites, collision detection, asset caching, and a basic UI.

See [`TODO.txt`](TODO.txt) and [`animation_plan.txt`](animation_plan.txt) for development notes. Some checklist entries predate the current implementation: movement, boundary reversal, JSON configuration integration, and automated tests already exist.

## License

Draco2D is distributed under the [MIT License](LICENSE).
