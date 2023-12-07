#pragma once

#include <SFML/Graphics.hpp>
#include "hero.h"
#include "bonus.h"
#include <fstream>
using namespace sf;
#include "json/nlohmann/json.hpp"
using json = nlohmann::json;

// Ñonstants
const int PHASE = 90;
const float NUMBER_PI = 3.141592654f;
const int PI_RADIAN = 180;
const float RADIUS_OF_PACKMAN = 20.f;

class Packman : public Hero
{
public:

	// fields
	sf::ConvexShape __topShape;
	sf::ConvexShape __bottomShape;
	sf::Vector2f __position;
	float __orientationDegrees;
	float __phaseAnimation;
	float __speed;
	unsigned int __eatenCookies;
	std::map<TypesBonuses, Bonus> __activeBonuses;

	// methods
	sf::Vector2f getRadialPoint(float angle, float radius);
	void assignFigure(sf::ConvexShape& shape, std::vector<sf::Vector2f> const& points);
	void initializePackman(Field& field, Packman& packman, float speed = 120.f);
	void assignPackmanFigure(sf::ConvexShape& topShape, sf::ConvexShape& bottomShape, const float phaseAnimation);
	void setSpeedMultiplier(float newSpeed);
	void updateHeroDirection();
	int directionOrientationDegrees(Direction direction);
	void updateHero(float elapsedTime, Field& field);
	void drawPackman(sf::RenderWindow& window);
	sf::FloatRect getPackmanBounds();
};