cmake_minimum_required(VERSION 3.5)

project(OpenDiva LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/Game.cpp src/Game.hpp src/Note.cpp src/Note.hpp src/NotePack.hpp src/Song.cpp src/Song.hpp src/Beatmap.cpp src/Beatmap.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/rapidjson/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
