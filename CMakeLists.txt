
cmake_minimum_required(VERSION 3.30.0)
project(EstherPlatformer VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

link_directories(${CMAKE_SOURCE_DIR}/src/libbox2d.a)
include_directories(${CMAKE_SOURCE_DIR}/include/box2d)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(EstherPlatformer 
    src/main.cpp 
    src/game.cpp
    src/entity.cpp
    src/player.cpp
    src/terrainElement.cpp
)
target_link_libraries(EstherPlatformer ${CMAKE_SOURCE_DIR}/src/libbox2d.a sfml-graphics sfml-window sfml-system)



set_property(TARGET EstherPlatformer PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)