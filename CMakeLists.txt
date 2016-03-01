cmake_minimum_required(VERSION 2.6)

project(RushHour)

add_definitions(-std=c99)


add_library(game piece.c game.c)

add_executable(RushHour gameTexte.c)
add_executable(test_piece1 test_piece1.c)
add_executable(test_game test_game.c)

target_link_libraries(RushHour game)
target_link_libraries(test_piece1 game)	
target_link_libraries(test_game game)

enable_testing()

add_test(test_piece test_piece1)

set_tests_properties (test_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")	








