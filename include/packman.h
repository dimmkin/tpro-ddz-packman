#pragma once

#include <SFML/Graphics.hpp>

class Field;

enum class Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Packman {
public:
	sf::CircleShape figure;
	Direction direction;
};