# Draco2D

2D engine created for educational purposes.

## Features

- **Core Engine**: Built using SDL3 and C++20.
- **Window Management**: Supports window creation, resizing, and manual closing.
- **2D Renderer**: A straightforward rendering loop for basic graphics.
- **Geometric Shapes**: Supports rendering of Triangles, Squares, and Rectangles.


Draco2D is a small 2D engine project written in C++ and built with CMake. The project is intended for learning engine architecture, rendering flow, input handling, and cross-platform development across macOS, Linux, and Windows.

The current setup uses SDL3 as the platform layer and CMake as the build system. SDL3 can be linked in modern CMake projects through `find_package(SDL3 REQUIRED)` and `target_link_libraries(... SDL3::SDL3)`, while CMake can generate native project files for Xcode on macOS and Visual Studio on Windows.

## Requirements

Install the following tools before configuring the project:

- CMake
- A C++20-capable compiler
- SDL3 development files
- A native build tool for your platform, Xcode on macOS, Ninja or Make on Linux, and Visual Studio or Ninja on Windows.

## Project structure

A typical configure step generates build files into a separate build directory such as `build`, `build-xcode`, or a platform-specific folder. This out-of-source workflow is the standard CMake approach and keeps generated files separate from source files.

## macOS

### Install dependencies

If Homebrew is available, install the basic dependencies with:

```bash
brew install cmake sdl3
```

Homebrew provides an install prefix for SDL3 that can be passed to CMake through `CMAKE_PREFIX_PATH` when `find_package(SDL3)` needs help locating the package on macOS.

### Generate an Xcode project

To generate the Xcode project:

```bash
cmake -S . -B build-xcode -G Xcode -DCMAKE_PREFIX_PATH=$(brew --prefix sdl3)
```

CMake officially supports the Xcode generator, which produces a `.xcodeproj` inside the selected build directory.

### Open and run in Xcode

Open the generated project with:

```bash
open build-xcode/Draco2D.xcodeproj
```

If your CMake `project()` name is different, replace `Draco2D.xcodeproj` with the generated project name. The Xcode generator is designed to create native Xcode project files and schemes for building and running targets on macOS.




### Run the application

After building, you can run the application by executing the binary in the `build-xcode` directory.

You can also build without opening Xcode:

```bash
cmake --build build-xcode --config Debug
```

## Linux

### Install dependencies

Install CMake, a compiler, and SDL3 using your distribution package manager. On Debian or Ubuntu, the exact SDL3 package name may vary by release, but CMake and compiler toolchains are typically installed through the system package manager.

An example setup may look like this:

```bash
sudo apt update
sudo apt install cmake g++ ninja-build
```

If SDL3 is packaged by your distribution, install its development package as well. If it is not available, build or install SDL3 separately and expose its CMake package path to the project through `CMAKE_PREFIX_PATH`.

### Configure and build

Using Ninja:

```bash
cmake -S . -B build-linux -G Ninja
cmake --build build-linux
```

If SDL3 is installed in a non-standard location:

```bash
cmake -S . -B build-linux -G Ninja -DCMAKE_PREFIX_PATH=/path/to/SDL3
cmake --build build-linux
```

CMake supports Ninja as a common cross-platform generator, and SDL3 documentation recommends standard CMake package discovery through `find_package`.

## Windows

### Install dependencies

Install one of the following toolchains:

- Visual Studio with the C++ workload
- Or Ninja plus a compatible compiler such as MSVC or Clang
- CMake
- SDL3 development files.

CMake can generate native Visual Studio project files, and Visual Studio also works well with CMake-based projects and presets.

### Generate a Visual Studio project

Example using the Visual Studio generator:

```powershell
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64
```

CMake documents the Visual Studio 17 2022 generator and its architecture selection through the `-A` option.

If SDL3 is not in a default search path, pass its install directory with `CMAKE_PREFIX_PATH`:

```powershell
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/path/to/SDL3"
```




### Run the application

After building, you can run the application by executing the binary in the `build-vs` directory.



## Generic CMake workflow

After configuration, the standard build command is:

```bash
cmake --build <build-directory>
```

For multi-configuration generators such as Xcode and Visual Studio, pass `--config Debug` or `--config Release` when needed. This behavior is part of how CMake generators map to native IDE build systems.

## Notes

- Keep source files under version control and ignore generated build directories such as `build/` and `build-xcode/`.
- Prefer CMake as the single source of truth for the build, even when using Xcode or Visual Studio as the IDE.
- If CMake cannot locate SDL3, verify the package path and pass it with `CMAKE_PREFIX_PATH`.
