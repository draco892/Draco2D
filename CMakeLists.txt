cmake_minimum_required(VERSION 3.25)

# Project metadata and supported language.
project(Draco2D
    VERSION 0.1.0
    DESCRIPTION "2d engine created for educational purposes"
    LANGUAGES CXX
)

# Require the project to use the C++23 standard
# and disable compiler-specific extensions.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable FetchContent so we can download dependencies
# automatically when they are not available on the system.
include(FetchContent)

# Prefer system-installed dependencies when available.
# If disabled, all supported third-party libraries will be fetched.
option(DRACO2D_PREFER_SYSTEM_DEPS
    "Prefer system-installed dependencies before FetchContent"
    ON
)

# ------------------------------------------------------------
# SDL3
# ------------------------------------------------------------
# First try to find SDL3 on the host system.
# This is the preferred path for local development machines.
if(DRACO2D_PREFER_SYSTEM_DEPS)
    find_package(SDL3 QUIET)
endif()

# If SDL3 is not available, fetch it from the official repository.
if(NOT SDL3_FOUND)
    # Build SDL as a shared library and disable optional targets
    # that are not needed by this project.
    set(SDL_SHARED ON CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
    set(SDL_DISABLE_INSTALL ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.14
    )

    FetchContent_MakeAvailable(SDL3)
endif()

# ------------------------------------------------------------
# nlohmann/json
# ------------------------------------------------------------
# First try to find nlohmann/json on the host system.
if(DRACO2D_PREFER_SYSTEM_DEPS)
    find_package(nlohmann_json 3.12.0 QUIET)
endif()

# If the package is not installed, fetch the official release archive.
if(NOT nlohmann_json_FOUND)
    # Disable tests and installation rules for the embedded dependency.
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    set(JSON_Install OFF CACHE INTERNAL "")

    FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    )

    FetchContent_MakeAvailable(json)
endif()

# Source files used to build the executable target.
set(SOURCES
    src/main.cpp
    # Application
    src//Application/Application.cpp
    # Window
    src//Window/Window.cpp
    src/Window/ConfigWindow.cpp
    # Render
    src/Render/Renderer2D.cpp
    # Configuration
    src/Configuration/ConfigManager.cpp
    # Base
    src/Base/BaseConfiguration.cpp
    src/Base/ErrorClass.cpp
    # Objects
    src/Objects/Triangle.cpp
    src/Objects/Square.cpp
    src/Objects/Rectangle.cpp
)

# Public and private header files included in the target.
set(HEADERS
    # Application
    include/Application/Application.hpp
    include/Application/ConfigApplication.hpp
    # Window
    include/Window/Window.hpp
    include/Window/ConfigWindow.hpp
    # Render
    include/Render/Renderer2D.hpp
    include/Render/ConfigRenderer2D.hpp
    # Configuration
    include/Configuration/ConfigManager.hpp
    # Base
    include/Base/BaseConfiguration.hpp
    include/Base/BaseObject.hpp
    include/Base/ErrorClass.hpp
    # Objects
    include/Objects/Triangle.hpp
    include/Objects/Square.hpp
    include/Objects/Rectangle.hpp
)

# Create the main executable target.
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add the local include directory so project headers can be found.
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Explicitly require C++23 support for this target.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Link third-party dependencies through their official CMake targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    nlohmann_json::nlohmann_json
)

# Define debug-only preprocessor symbols.
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:D2D_DEBUG=1>
)

# Enable a stricter warning level depending on the compiler.
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set the final output binary name.
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "Draco2D"
)

# Generate an Xcode scheme when building on Apple platforms.
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_GENERATE_SCHEME ON
    )
endif()

# Perform a basic compiler version check to reduce the risk of
# configuring the project with a toolchain that is too old for C++23.
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
        message(FATAL_ERROR
            "C++23 requires a newer compiler. Current compiler: "
            "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
        )
    endif()
elseif(MSVC)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.30)
        message(FATAL_ERROR
            "C++23 requires MSVC 19.30 or newer. Current version: "
            "${CMAKE_CXX_COMPILER_VERSION}"
        )
    endif()
endif()