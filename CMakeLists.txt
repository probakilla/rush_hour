cmake_minimum_required(VERSION 2.6)

project(RushHour)

add_executable(RushHour
		game.c
		piece.c
		test_piece1.c
		test_game.c
		gameTexte.c)

set_property(TARGET RushHour PROPERTY C_STANDARD 99)


