cmake_minimum_required(VERSION 2.6)

project(rush_hour)

add_definitions(-std=c99)

add_library (game game.c piece.c game_texte.c game_texte.h)

add_executable(rush_hour game_texte.c game.c piece.c rush_hour.c)
add_executable(test_piece1 test_piece1.c)
add_executable(test_game test_game.c)

target_link_libraries (rush_hour game)
target_link_libraries (test_piece1 game)
target_link_libraries (test_game game)

enable_testing()

add_test(test_piece test_piece1)
add_test(test_game test_game)

set_tests_properties(test_piece PROPERTIES TIMEOUT 3)
set_tests_properties(test_game PROPERTIES TIMEOUT 3)




