cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(EgyptAdventure ${SOURCES})

if (WIN32)
    target_link_libraries(EgyptAdventure winmm)
endif()
