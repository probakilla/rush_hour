cmake_minimum_required(VERSION 2.6)

project(rush_hour)

add_definitions(-std=c99 -Wall -O2 -g)

include_directories(include)

add_library (game src/game.c src/piece.c src/game_text.c)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/lib)

add_executable(rush_hour src/game_text.c src/game.c src/piece.c src/rush_hour.c)
add_executable(ane_rouge src/ane_rouge.c src/game_text.c src/game.c src/piece.c)
add_executable(test_piece1 src/test_piece1.c)
add_executable(test_game src/test_game.c)

target_link_libraries (rush_hour game)
target_link_libraries (ane_rouge game)
target_link_libraries (test_piece1 game)
target_link_libraries (test_game game) 

install(TARGETS rush_hour test_game test_piece1 ane_rouge DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(TARGETS game DESTINATION ${LIBRARY_OUTPUT_PATH})

enable_testing()

add_test(test_piece RushHour/bin/test_piece1)
add_test(test_game RushHour/bin/test_game)

set_tests_properties(test_piece PROPERTIES TIMEOUT 3)
set_tests_properties(test_game PROPERTIES TIMEOUT 3)




