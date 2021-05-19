cmake_minimum_required(VERSION 3.1.0)

project(qt-pong)
set(qt-pong VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Multimedia Network REQUIRED)

add_executable(qt-pong
    src/main.cpp
    src/main_window.cpp
    src/scene.cpp
    src/ball.cpp
    src/config.cpp
    src/paddle.cpp
    src/view.cpp
    src/player.cpp
    src/config_window.cpp
    src/controls_config_window.cpp
    src/audio_config_window.cpp
    src/multiplayer_window.cpp
    src/multiplayer_game.cpp
    include/main_window.h
    include/scene.h
    include/ball.h
    include/config.h
    include/paddle.h
    include/view.h
    include/player.h
    include/config_window.h
    include/controls_config_window.h
    include/audio_config_window.h
    include/multiplayer_window.h
    include/multiplayer_game.h
)

target_link_libraries(qt-pong
    PUBLIC
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::Network
)
