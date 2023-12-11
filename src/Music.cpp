#include "../include/Music.h"

GameMusic::GameMusic()
{
	// Array of file names and music paths
	std::array<std::string, _count_game_music>nameFile{ "sound/PacMan_Tem.ogg", "sound/Staring_fun.ogg", 
	"sound/f_Map_1.ogg", "sound/f_Map_2.ogg", "sound/f_Map_3.ogg", "sound/f_1.ogg",  
	"sound/f_2.ogg", "sound/f_3.ogg", "sound/f_4.ogg", "sound/f_4.ogg", "sound/f_6.ogg", "sound/f_7.ogg" };

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


int GameMusic::Random_music()
{
	int min = 2;
	int max = _count_game_music - 1;
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

void GameMusic::Music_play_Map(bool isFirstMusic, int positionMusic)
{
    std::ifstream file("text.json");
    json startMap = json::parse(file);
    file.close();
    int index = startMap["Start_game"][2];
	  index = (isFirstMusic) ? index += 2 : positionMusic;
	  _game_musics[index].setLoop(true);
	  if (_game_musics[index].getStatus() == sf::Music::Stopped) { _game_musics[index].play(); }
	  if (_game_musics[index].getStatus() == sf::Music::Paused) { _game_musics[index].play(); }
}