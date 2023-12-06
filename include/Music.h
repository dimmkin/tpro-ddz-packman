#pragma once
#include <SFML\Audio.hpp>
#include <array>

class GameMusic
{
	static const int _count_game_music = 1;
	std::array<sf::Music, _count_game_music> _game_musics;

public:
	GameMusic();
	~GameMusic() = default;
	void Music_play(int index);
	void Music_stop(int index);
	void Music_set_volume_all(int volume);
};