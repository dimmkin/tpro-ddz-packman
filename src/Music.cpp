#include "Music.h"

GameMusic::GameMusic()
{
	// Array of file names and music paths
	std::array<std::string, _count_game_music>nameFile{ "music/PacMan_Tem.ogg", "music/Staring_fun.ogg", "music/f_1.ogg",  "music/f_2.ogg", "music/f_3.ogg", "music/f_4.ogg", "music/f_4.ogg", "music/f_6.ogg", "music/f_7.ogg"};

	// Assigning music to music objects
	for (int index = 0; index != _count_game_music; ++index) {
		if (!_game_musics[index].openFromFile(nameFile[index])) exit(1);
	}

	// Background music should be playing constantly
	_game_musics[0].setLoop(true);
}

void GameMusic::Music_play(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
}

void GameMusic::Music_play_always(int index)
{
	_game_musics[0].setLoop(true);
	if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
}

void GameMusic::Music_stop(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].stop(); }
}

void GameMusic::Music_pause(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].pause(); }
}

void GameMusic::Music_return(int index)
{
	if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].play(); }
}


void GameMusic::Music_set_volume_all(int volume)
{
	for (int index = 0; index != _count_game_music; ++index)
		_game_musics[index].setVolume(volume);
}

int GameMusic::Random_music(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}

void GameMusic::Music_stop_all()
{
	for (int index = 0; index != _count_game_music; ++index)
	{
		if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].stop(); }
	}
}

void GameMusic::Music_pause_all()
{
	for (int index = 0; index != _count_game_music; ++index)
	{
		if (_game_musics[index].getStatus() == sf::Music::Playing) { _game_musics[index].pause(); }
	}
}