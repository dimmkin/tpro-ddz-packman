#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include <chrono>

class Field;

// constants
static const sf::IntRect FRAME_EYES_LEFT(0, 0, 32, 32);
static const sf::IntRect FRAME_EYES_TOP(32, 0, 32, 32);
static const sf::IntRect FRAME_EYES_RIGHT(64, 0, 32, 32);
static const sf::IntRect FRAME_EYES_BOTTOM(96, 0, 32, 32);

// paths
const char GREEN_GHOST_TEXTURE[] = "image/ghost-green.png";
const char PINK_GHOST_TEXTURE[] = "image/ghost-pink.png";
const char RED_GHOST_TEXTURE[] = "image/ghost-red.png";
const char ORANGE_GHOST_TEXTURE[] = "image/ghost-orange.png";


enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Hero
{
public:

	// fields
	sf::RectangleShape figure;
	sf::Texture texture;
	Direction direction;

	// methods
	Direction randomDirection(Direction previousDirection);
	void updateHeroDirection();
	bool initializeHero(const sf::Vector2f& position, const std::string& texturePath);
	sf::Vector2f buildMovement(sf::Vector2f& movement, Hero& hero, const float step);
	void MovingOut(Field& field, sf::Vector2f& movement, const float speed);
	void updateHero(float elapsedTime, Field& field, const float speed);
	void drawHero(sf::RenderWindow& window);
	void drawEyes();
};
