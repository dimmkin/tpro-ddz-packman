#pragma once

#include <SFML/Graphics.hpp>
#include <array>
using namespace sf;

class GameSelect
{
    static const int _count_rounds_name = 4;
    std::array<std::string, _count_rounds_name> _rounds_name;
    static const int _count_game_name = 2;
    std::array<std::string, _count_game_name> _game_name;
   
public:
    GameSelect();
    ~GameSelect() = default;
    std::string CurrentRound(int index);
    bool isClassic(std::string gameName);
};

