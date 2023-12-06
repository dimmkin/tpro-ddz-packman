#pragma once

#include <SFML/Graphics.hpp>
#include "hero.h"
#include "bonus.h"
#include <fstream>
using namespace sf;
#include "json/nlohmann/json.hpp"
using json = nlohmann::json;

// сonstants
const int PHASE = 90;
const float NUMBER_PI = 3.141592654f;
const int PI_RADIAN = 180;
const float RADIUS_OF_PACKMAN = 20.f;

class Packman : public Hero
{
public:

	// fields
	sf::ConvexShape topShape;
	sf::ConvexShape bottomShape;
	sf::Vector2f position;
	float orientationDegrees;
	float phaseAnimation;
	float speed;
	unsigned int eatenCookies;
	std::map<TypesBonuses, Bonus> activeBonuses;

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