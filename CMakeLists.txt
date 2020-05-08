cmake_minimum_required(VERSION 3.10)

project(OpenDIVA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OpenDIVA src/OpenDIVA.cpp src/Beatmap.cpp src/Level.cpp src/Sprite.cpp)
target_include_directories(OpenDIVA PUBLIC thirdparty/rapidjson/include)
target_link_libraries(OpenDIVA PUBLIC SDL2)

add_executable(test src/test.cpp src/Sprite.cpp)
target_link_libraries(test PUBLIC SDL2)
