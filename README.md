# Draco2D

A clean and modular 2D rendering engine built for educational purposes.

## Features

- **Core Engine**: Built using SDL3 and C++20.
- **Window Management**: Support for window creation, resizing, and standard window management.
- **2D Renderer**: A straightforward rendering loop for basic graphics.
- **Geometric Shapes**: Built-in support for Triangles, Squares, and Rectangles.
- **Robust Error Handling**: A centralized system for error reporting and tracking.
- **Configurable Systems**: Easy-to-use configuration system for engine parameters.

## Design Philosophy

Draco2D is designed with a modular architecture in mind, making it an excellent project for learning engine architecture, rendering flow, and cross-platform development.

### Architecture Overview

The project is divided into several key modules:

- **Application**: Manages the high-level life cycle of the application, including the main game loop, event handling, and basic update/render calls.
- **Rendering**: Provides a simplified interface for 2D rendering, abstracting SDL3's underlying complexities.
- **Objects**: A collection of game objects inheriting from a unified `BaseObject` class, ensuring a consistent interface for updating and rendering.
- **Base**: Core utilities including file/stream management, validation, and an extensive error-handling system.
- **Configuration**: A system for loading and managing application settings, allowing for dynamic configuration of the engine's behavior.

## Key Systems

### Error Handling
Draco2D features a robust error-handling system. It provides descriptive error messages for common issues including:
- SDL initialization failures
- Window/Renderer creation issues
- File system errors (Missing files, permissions, etc.)
- Configuration and validation errors

### Filesystem Interaction
Includes tested wrappers for reading and writing files, ensuring that file existence and access permissions are verified before operations.

### Configuration System
Simple loading of parameters from JSON files, allowing you to tweak window size, v-sync, and default colors without recompiling.

## Requirements

Install the following tools before configuring the project:

- CMake
- A C++20-capable compiler
- SDL3 development files
- A platform-specific build tool (Xcode on macOS, Ninja or Make on Linux, and Visual Studio or Ninja on Windows)

## Project Structure

- `src/`: Source files for the application.
- `include/`: Header files for the project's public API.
- `base/`: Core library for error handling, file I/O, and validation.
- `Objects/`: Representations of 2D geometric shapes.
- `Render/`: The 2D rendering abstraction layer.
- `Application/`: The main engine wrapper and game loop.

## Development Workflow

The project uses an out-of-source build workflow. Configuration is performed by CMake, and build files are generated into a separate `build/` directory.

### macOS

Install basic dependencies:
```bash
brew install cmake sdl3
```

Generate an Xcode project:
```bash
cmake -S . -B build-xcode -G Xcode -DCMAKE_PREFIX_PATH=$(brew --prefix sdl3)
```

Open and run:
```bash
open build-xcode/Draco2D.xcodeproj
```

### Linux

Install CMake, a compiler, and SDL3:
```bash
sudo apt update
sudo apt install cmake g++ ninja-build
```

Configure and build:
```bash
cmake -S . -B build-linux -G Ninja
cmake --build build-linux
```

If SDL3 is in a non-standard location, provide `CMAKE_PREFIX_PATH`:
```bash
cmake -S . -B build-linux -G Ninja -DCMAKE_PREFIX_PATH=/path/to/SDL3
cmake --build build-linux
```

### Windows

Install a compatible toolchain (Visual Studio with C++ workload or Ninja with a MSVC/Clang compiler).

Generate a Visual Studio project:
```powershell
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64
```

If SDL3 is not in the path:
```powershell
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/path/to/SDL3"
```

## General Build Commands

To build for any platform, run:
```bash
cmake --build <build-directory>
```

For multi-config generators (like Xcode and Visual Studio), specify the configuration:
```bash
cmake --build <build-directory> --config Debug
```

## Notes

- Keep source files under version control and ignore generated build directories (e.g. `build/`, `build-xcode/`).
- Use CMake as the single source of truth for the build configuration.
- Ensure `CMAKE_PREFIX_PATH` is correctly set for SDL3 to avoid detection issues.
