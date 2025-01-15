cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(EgyptAdventureLib ${SOURCES}
        src/items/amulets/HealthAmulet.cpp
        src/items/amulets/HealthAmulet.cpp
        src/items/amulets/HealthAmulet.hpp
        src/items/amulets/ArmorAmulets.cpp
        src/items/amulets/ArmorAmulets.hpp)

add_executable(EgyptAdventure src/main.cpp)
target_link_libraries(EgyptAdventure PRIVATE EgyptAdventureLib)

add_executable(battle_test "test/battleTest.cpp"
        src/BattleSystem.hpp)
target_link_libraries(battle_test PRIVATE EgyptAdventureLib)

add_executable(map_test "test/mapTest.cpp"
    src/map/MapGenerator.hpp)
target_link_libraries(map_test PRIVATE EgyptAdventureLib)

add_test(NAME MapTest COMMAND map_test)
add_test(NAME BattleTest COMMAND battle_test)

if (WIN32)
    target_link_libraries(EgyptAdventureLib winmm)
endif()