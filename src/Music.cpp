#include "Music.h"

GameMusic::GameMusic()
{
	// Array of file names and music paths
	std::array<std::string, _count_game_music>nameFile{ "music/PacMan_Tem.ogg" };

	// Assigning music to music objects
	for (int index = 0; index != _count_game_music; ++index) {
		if (!_game_musics[index].openFromFile(nameFile[index])) {
			// ToDo thinking about...
		}
	}

	// Background music should be playing constantly
	_game_musics[0].setLoop(true);
}

void GameMusic::Music_play(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
}

void GameMusic::Music_stop(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].stop(); }
}

void GameMusic::Music_set_volume_all(int volume)
{
	for (int index = 0; index != _count_game_music; ++index)
		_game_musics[index].setVolume(volume);
}
