cmake_minimum_required(VERSION 3.25)

project(Draco2D
    VERSION 0.1.0
    DESCRIPTION "2d engine created for educational purposes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Draco2D
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer2D.cpp
    
    include/errors.h
    include/Application.hpp
    include/Window.hpp
    include/Renderer2D.hpp
    
)

target_include_directories(Draco2D PRIVATE include)

target_compile_features(Draco2D PRIVATE cxx_std_20)

find_package(SDL3 REQUIRED)

target_link_libraries(Draco2D PRIVATE SDL3::SDL3)

target_compile_definitions(Draco2D PRIVATE
    $<$<CONFIG:Debug>:D2D_DEBUG=1>
)

if(MSVC)
    target_compile_options(Draco2D PRIVATE /W4 /permissive-)
else()
    target_compile_options(Draco2D PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(Draco2D PROPERTIES
    OUTPUT_NAME "Draco2D"
)

if(APPLE)
    set_target_properties(Draco2D PROPERTIES
        XCODE_GENERATE_SCHEME ON
    )
endif()
