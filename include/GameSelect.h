/**
 * @file GameSelect.h
 * @brief Содержит объявление класса GameSelect. 
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <array>
using namespace sf;

/**
 * @class GameSelect
 * 
 * @brief Представляет обработчик режима игры игры.
 * 
 */
class GameSelect
{
    /// @brief Количество всех названий раундов.
    static const int _count_rounds_name = 4;

    /// @brief Массив названий раундов.
    std::array<std::string, _count_rounds_name> _rounds_name;

    /// @brief Количество всех названий режимов игры.
    static const int _count_game_name = 2;

    /// @brief Массив названий режимов игры.
    std::array<std::string, _count_game_name> _game_name;
   
public:

	/**
	 * @brief Заполняет массивы необходимыми названиями раундов и режимов.
	 * 
	 * @code
     * GameSelect::GameSelect()
     *{
     *  std::array<std::string, _count_rounds_name> roundsName{"ROUND 1/1", "ROUND 1/3", "ROUND 2/3", "ROUND 3/3"};
     *  for (int index = 0; index != _count_rounds_name; ++index) {
     *      _rounds_name[index] = roundsName[index];
     *  }
     *
     *  std::array<std::string, _count_game_name> gameName{"Classic", "Fast Game"};
     *  for (int index = 0; index != _count_game_name; ++index) {
     *      _game_name[index] = gameName[index];
     *  }
     *}
	 * @endcode
	 */
    GameSelect();

    /// @brief Чистка массива с данными о раундах и режимах не требуется.
    ~GameSelect() = default;

    /**
	 * @brief Выводит название раунда по указанному индексу.
	 * 
	 * @param index Номер раунда в массиве.
     * 
     * @return Название раунда.
	 * 
	 * @code
     * std::string GameSelect::CurrentRound(int index)
     *{
     *  if(index > 3)exit(1);
     *  return _rounds_name[index];
     *}
	 * @endcode
	 */
    std::string CurrentRound(int index);

    /**
	 * @brief Проверяет классический режим или нет.
	 * 
	 * @param gameName Название режима.
     * 
     * @return Логическое значение, показывающее, является ли режим классическим.
	 * 
	 * @code
     * bool GameSelect::isClassic(std::string gameName)
     *{
     *  return gameName == _game_name[0];
     *}
	 * @endcode
	 */
    bool isClassic(std::string gameName);
};

