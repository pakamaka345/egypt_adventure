cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(EgyptAdventure ${SOURCES}
        src/Bullet.cpp
        src/Inventory.cpp
        include/PriorityQueue.hpp
        include/tiles/TileType.hpp
        include/tiles/WallTile.hpp
        src/WallTile.cpp
        include/tiles/FloorTile.hpp
        src/FloorTile.cpp
)

if (WIN32)
    target_link_libraries(EgyptAdventure winmm)
endif()
