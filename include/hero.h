#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include <chrono>

class Field;

enum class Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Hero {
public:
	sf::CircleShape figure;
	Direction direction;

	Direction randomDirection(Direction previousDirection);
	void updateHeroDirection(Hero& hero);
	void initializeHero(Hero& hero, const sf::Vector2f& position, const float radius, const sf::Color color);
	sf::Vector2f buildMovement(sf::Vector2f& movement, Hero& hero, const float step);
	void MovingOut(Field& field, Hero& hero, sf::Vector2f& movement, const float speed);
	void updateHero(Hero& hero, float elapsedTime, Field& field, const float speed);
	void drawHero(sf::RenderWindow& window, const Hero& hero);
};
