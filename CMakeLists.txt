cmake_minimum_required(VERSION 3.1.0)
project(OpenDIVA)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include thirdparty/rapidjson/include)

add_executable(OpenDIVA
        src/main.cpp
        src/Note.cpp
        include/OpenDIVA/Note.hpp src/Gui.cpp include/OpenDIVA/Gui.hpp src/SongLoader.cpp include/OpenDIVA/SongLoader.hpp src/Type.cpp include/OpenDIVA/Type.hpp include/OpenDIVA/Grade.hpp)

target_link_libraries(OpenDIVA Qt5::Widgets)