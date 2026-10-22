cmake_minimum_required(VERSION 3.16)
project(tic_tac_toe VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(ttt_core
    src/Board.cpp
    src/Game.cpp
)
target_include_directories(ttt_core PUBLIC src)

add_executable(tic_tac_toe src/main.cpp)
target_link_libraries(tic_tac_toe PRIVATE ttt_core)

enable_testing()
add_executable(ttt_tests tests/test_board.cpp)
target_link_libraries(ttt_tests PRIVATE ttt_core)
add_test(NAME ttt_tests COMMAND ttt_tests)
