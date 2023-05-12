cmake_minimum_required(VERSION 3.25)
project(LudoGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(LudoGame main.cpp AI_player/ai_player.h AI_player/ai_player.cpp AI_player/MyAiPlayer.cpp AI_player/MyQTable.cpp AI_player/q_table.cpp Domain_Code/dice.h Domain_Code/game.cpp Domain_Code/test_game.cpp Players/move_logic.cpp Players/player_aggro_fast.h Players/player_fast.h Players/player_random.h Players/player_random_safe.h )
