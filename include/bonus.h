#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Field;

// constants
static const sf::IntRect FRAME_BOMB(0, 0, 32, 32);
static const sf::IntRect FRAME_CYCLE(32, 0, 32, 32);

// paths
const char BONUSES_TEXTURE[] = "image/bonus.png";

enum class TypesBonuses {
	BOMB,
	CYCLE
};

class Bonus
{
public:
	// fields
	sf::RectangleShape __figure;
	sf::Texture __texture;
	TypesBonuses __bonusType;
	bool __active;
	unsigned int __eatenDots;
	unsigned int __remainingDots;

	// methods
	bool initializeBonus(const sf::Vector2f& position, const std::string& texturePath, const sf::IntRect frame, TypesBonuses type, bool active);
	void drawBonus(sf::RenderWindow& window);
};