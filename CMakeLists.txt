cmake_minimum_required(VERSION 2.6)

project(rush_hour)

#include(CodeCoverage)

set(CMAKE_C_FLAGS "-std=c99 -O0 -g -Wcast-qual -pedantic-errors -fprofile-arcs -ftest-coverage -Wall")
set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage -O0 -g ")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

include_directories(include)

add_library (game src/game.c src/piece.c)
add_library (queue src/queue.c)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/lib)

add_executable(rush_hour src/game_text.c src/rush_hour.c)
add_executable(ane_rouge src/ane_rouge.c src/game_text.c)
add_executable(test_piece1 src/test_piece1.c)
add_executable(test_game src/test_game.c)
add_executable(solver src/solver.c)
add_executable(test_solver src/test_solver.c)
add_executable(test_queue src/test_queue.c)

target_link_libraries (rush_hour game)
target_link_libraries (ane_rouge game)
target_link_libraries (test_piece1 game)
target_link_libraries (test_game game)
target_link_libraries (solver queue game)
target_link_libraries (test_solver queue)
target_link_libraries (test_queue queue game)


install(TARGETS rush_hour test_game test_piece1 ane_rouge solver test_solver test_queue DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(TARGETS game queue DESTINATION ${LIBRARY_OUTPUT_PATH})

enable_testing()

add_test(test_piece RushHour/bin/test_piece1)
add_test(test_game RushHour/bin/test_game)
add_test(test_queue RushHour/bin/test_queue)
add_test(test_solver RushHour/bin/test_solver)

set_tests_properties(test_piece PROPERTIES TIMEOUT 3)
set_tests_properties(test_game PROPERTIES TIMEOUT 3)
set_tests_properties(test_queue PROPERTIES TIMEOUT 3)
set_tests_properties(test_solver PROPERTIES TIMEOUT 3)

