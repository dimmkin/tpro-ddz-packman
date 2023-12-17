/**
 * @file Music.h
 * @brief Содержит объявление класса Music. 
 */
#pragma once
#include <SFML/Audio/Music.hpp>
#include <array>
#include <random>
#include <fstream>
#include "../json/nlohmann/json.hpp"
using json = nlohmann::json;

/**
 * @class GameMusic
 * 
 * @brief Представляет все звуковоспроизведения во время игры.
 * 
 */
class GameMusic
{
	/// @brief Количество всех наборов звуков во время игры
	static const int _count_game_music = 12;

	/// @brief Массив со звуками для игры
	std::array<sf::Music, _count_game_music> _game_musics;

public:

	/**
	 * @brief Заполняет массив необходимыми звуками.
	 * 
	 * @code
	 * GameMusic::GameMusic()
	 *{
	 *	std::array<std::string, _count_game_music>nameFile{ "sound/PacMan_Tem.ogg", "sound/Staring_fun.ogg", 
	 *	"sound/f_Map_1.ogg", "sound/f_Map_2.ogg", "sound/f_Map_3.ogg", "sound/f_1.ogg",  
	 *	"sound/f_2.ogg", "sound/f_3.ogg", "sound/f_4.ogg", "sound/f_4.ogg", "sound/f_6.ogg", "sound/f_7.ogg" };
	 *
	 *	for (int index = 0; index != _count_game_music; ++index) {
	 *		if (!_game_musics[index].openFromFile(nameFile[index])) exit(1);
	 *	}
	 *
	 *	_game_musics[0].setLoop(true);
	 *}
	 * @endcode
	 */
	GameMusic();

	/// @brief Чистка массива с музыкой не требуется.
	~GameMusic() = default;

	/**
	 * @brief Воспроизводит звук по указанному индексу.
	 * 
	 * @param index Номер звука в массиве.
	 * 
	 * @code
	 * void GameMusic::Music_play(int index)
	 *{
	 *	if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
	 *}
	 * @endcode
	 */
	void Music_play(int index);

	/**
	 * @brief Останавливает звук по указанному индексу.
	 * 
	 * @param index Номер звука в массиве.
	 * 
	 * @code
	 * void GameMusic::Music_stop(int index)
	 *{
	 * 	 if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].stop(); }
	 *}
	 * @endcode
	 */
	void Music_stop(int index);

	/**
	 * @brief Устанавливает громкость для всех аудио.
	 * 
	 * @param volume Процент громкости.
	 * 
	 * @code
	 * void GameMusic::Music_set_volume_all(int volume)
	 *{
	 *	for (int index = 0; index != _count_game_music; ++index)
	 *		_game_musics[index].setVolume(volume);
	 *}
	 * @endcode
	 */
	void Music_set_volume_all(int volume);

	/**
	 * @brief Ставит на паузу звук по указанному индексу.
	 * 
	 * @param index Номер звука в массиве.
	 * 
	 * @code
	 * void GameMusic::Music_pause(int index)
	 *{
	 *	if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].pause(); }
	 *}
	 * @endcode
	 */
	void Music_pause(int index);

	/**
	 * @brief Воспроизводит поставленный на паузу звук по указанному индексу.
	 * 
	 * @param index Номер звука в массиве.
	 * 
	 * @code
	 * void GameMusic::Music_return(int index)
	 *{
	 *	if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].play(); }
	 *}
	 * @endcode
	 */
	void Music_return(int index);

	/**
	 * @brief Выдает случайный номер звука.
	 * 
	 * @return Индекс звука.
	 * 
	 * @code
	 * int GameMusic::Random_music()
	 *{
	 *	int min = 2;
	 *	int max = _count_game_music - 1;
	 *	std::random_device rd;
	 *	std::mt19937 mt(rd());
	 *	std::uniform_int_distribution<int> dist(min, max);
	 *
	 *	return dist(mt);
	 *}
	 * @endcode
	 */
	int Random_music();

	/**
	 * @brief Прекращает воспроизведение всех аудио.
	 * 
	 * @code
	 * void GameMusic::Music_stop_all()
	 *{
	 *	for (int index = 0; index != _count_game_music; ++index)
	 *	{
	 *		if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].stop(); }
	 *	}
	 *}
	 * @endcode
	 */
	void Music_stop_all();

	/**
	 * @brief Ставит на паузу воспроизведение всех аудио.
	 * 
	 * @code
	 * void GameMusic::Music_pause_all()
	 *{
	 *	for (int index = 0; index != _count_game_music; ++index)
	 *	{
	 *		if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].pause(); }
	 *	}
	 *}
	 * @endcode
	 */
	void Music_pause_all();

	/**
	 * @brief Воспроизводит музыку во время процесса игры.
	 * 
	 * @param isFirstMusic Логическое значение, указывающее, является ли воспроизведение первым. 
	 * @param positionMusic Индекс звука(по умолчанию 8). 
	 * 
	 * @code
	 * void GameMusic::Music_play_Map(bool isFirstMusic, int positionMusic)
	 *{
	 *	std::ifstream file("text.json");
	 *	json startMap = json::parse(file);
	 *	file.close();
	 *	int index = startMap["Start_game"][2];
	 *	index = (isFirstMusic) ? index += 2 : positionMusic;
	 *	_game_musics[index].setLoop(true);
	 *	if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
	 *	if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].play(); }
	 *}
	 * @endcode
	 */
	void Music_play_Map(bool isFirstMusic, int positionMusic = 8);

	/**
	 * @brief Воспроизводит все аудио поставленные на паузу.
	 * 
	 * @code
	 * void GameMusic::Music_return_all()
	 *{
	 *	for (int index = 0; index != _count_game_music; ++index)
	 *	{
	 *		if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].play(); }
	 *	}
	 *}
	 * @endcode
	 */
	void Music_return_all();

	/**
	 * @brief Ставит все аудио на паузу.
	 * 
	 * @code
	 *void GameMusic::Music_stop_paused_all()
	 *{
	 *	for (int index = 0; index != _count_game_music; ++index)
	 *	{
	 *		if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].stop(); }
	 *	}
	 *}
	 * @endcode
	 */
	void Music_stop_paused_all();
};