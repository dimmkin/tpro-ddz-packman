#include "../include/GameSelect.h"

GameSelect::GameSelect()
{
    std::array<std::string, _count_rounds_name> roundsName{"ROUND 1/1", "ROUND 1/3", "ROUND 2/3", "ROUND 3/3"};
    for (int index = 0; index != _count_rounds_name; ++index) {
        _rounds_name[index] = roundsName[index];
	}

    std::array<std::string, _count_game_name> gameName{"Classic", "Fast Game"};
    for (int index = 0; index != _count_game_name; ++index) {
        _game_name[index] = gameName[index];
	}
}

std::string GameSelect::CurrentRound(int index)
{
    if(index > 3)exit(1);
    return _rounds_name[index];
}

bool GameSelect::isClassic(std::string gameName)
{
    return gameName == _game_name[0];
}
