cmake_minimum_required(VERSION 3.25)

project(Draco2D
    VERSION 0.1.0
    DESCRIPTION "2d engine created for educational purposes"
    LANGUAGES CXX
)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(SDL3 REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer2D.cpp
    src/Objects/Triangle.cpp
    src/Objects/Square.cpp
    src/Objects/Rectangle.cpp
)

# Header files
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

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Compile features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:D2D_DEBUG=1>
)

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Output name
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "Draco2D"
)

# Platform-specific
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_GENERATE_SCHEME ON
    )
endif()