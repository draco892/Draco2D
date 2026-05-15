cmake_minimum_required(VERSION 3.25)

# Project metadata and supported language
project(Draco2D
    VERSION 0.1.0
    DESCRIPTION "2d engine created for educational purposes"
    LANGUAGES CXX
)

# Require the project to be compiled with the C++23 standard
# and disable compiler-specific language extensions.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate required third-party dependencies.
find_package(SDL3 REQUIRED)

# Source files used to build the executable target.
set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer2D.cpp
    src/Objects/Triangle.cpp
    src/Objects/Square.cpp
    src/Objects/Rectangle.cpp
)

# Public and private header files included in the target.
# Listing headers is not strictly required for compilation,
# but it helps IDE integration and project organization.
set(HEADERS
    include/errors.h
    include/Application.hpp
    include/Window.hpp
    include/Renderer2D.hpp
    include/Base/BaseObject.hpp
    include/Objects/Triangle.hpp
    include/Objects/Square.hpp
    include/Objects/Rectangle.hpp
)

# Create the main executable for the engine.
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add the local include directory so project headers can be found.
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Explicitly require C++23 support for this target.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Link SDL3 to the executable target.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

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