cmake_minimum_required(VERSION 2.6)

project(rush_hour)

add_definitions(-std=c99 -Wall -g)

add_library (game game.c piece.c game_text.c)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/lib)
SET(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RushHour/include)

add_executable(rush_hour game_text.c game.c piece.c rush_hour.c)
add_executable(ane_rouge ane_rouge.c game_text.c game.c piece.c)
add_executable(test_piece1 test_piece1.c)
add_executable(test_game test_game.c)

target_link_libraries (rush_hour game)
target_link_libraries (ane_rouge game)
target_link_libraries (test_piece1 game)
target_link_libraries (test_game game) 

install(TARGETS rush_hour test_game test_piece1 ane_rouge DESTINATION ${EXECUTABLE_OUTPUT_PATH})
install(TARGETS game DESTINATION ${LIBRARY_OUTPUT_PATH})
install(FILES game.h piece.h game_text.h DESTINATION ${CMAKE_INCLUDE_PATH})
enable_testing()

add_test(test_piece test_piece1)
add_test(test_game test_game)

set_tests_properties(test_piece PROPERTIES TIMEOUT 3)
set_tests_properties(test_game PROPERTIES TIMEOUT 3)




