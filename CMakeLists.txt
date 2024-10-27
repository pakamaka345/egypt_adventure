cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(include/enums)


add_executable(EgyptAdventure 
    src/main.cpp 
    src/Map.cpp 
    src/Tile.cpp 
    src/Item.cpp 
    src/Entity.cpp
    src/Player.cpp
    src/Torch.cpp
)

if (WIN32)
    target_link_libraries(EgyptAdventure winmm)
endif()
