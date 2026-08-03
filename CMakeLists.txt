cmake_minimum_required(VERSION 3.22...4.4)

project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

include(FetchContent)

FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)


set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(PhysicsEngine 
                        src/main.cpp
                        src/ball.cpp
                        src/application.cpp
                        src/universal.cpp)

target_include_directories(PhysicsEngine
                        PRIVATE
                            ${IMGUI_DIR}/misc/cpp
                            include)       

target_link_libraries(PhysicsEngine 
                    PRIVATE
                        SFML::Graphics 
                        SFML::Window 
                        SFML::System
                        ImGui-SFML::ImGui-SFML)