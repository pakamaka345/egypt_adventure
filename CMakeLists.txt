cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(EgyptAdventureLib ${SOURCES}
        include/effects/GroupAttackBonus.hpp
        src/GroupAttackBonus.cpp
        include/effects/SandShield.hpp
        src/SandShield.cpp
        src/SandTile.cpp
        include/config/Config.hpp
        include/nlohmann/json.hpp
        src/Config.cpp)

add_executable(EgyptAdventure src/main.cpp)
target_link_libraries(EgyptAdventure PRIVATE EgyptAdventureLib)

add_executable(battle_test "test/battleTest.cpp")
target_link_libraries(battle_test PRIVATE EgyptAdventureLib)

add_test(NAME BattleTest COMMAND battle_test)

if (WIN32)
    target_link_libraries(EgyptAdventureLib winmm)
endif()