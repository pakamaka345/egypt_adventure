cmake_minimum_required(VERSION 3.10)

project(EgyptAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(include/enums)

add_executable(EgyptAdventure src/main.cpp)

if (WIN32)
    target_link_libraries(EgyptAdventure winmm)
endif()

add_custom_command(TARGET EgyptAdventure
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running EgyptAdventure..."
    COMMAND ${CMAKE_COMMAND} -E env PATH=$<TARGET_FILE_DIR:EgyptAdventure> $<TARGET_FILE:EgyptAdventure>
)