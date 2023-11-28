#pragma once

#include <SFML/Graphics.hpp>
#include "hero.h"

class Packman : public Hero
{
public:
	sf::ConvexShape topShape;
	sf::ConvexShape bottomShape;
	sf::Vector2f position;

	float orientationDegrees;
	float phaseAnimation;

	unsigned int eatenCookies;


	sf::Vector2f getRadialPoint(float angle, float radius);
	void assignShape(sf::ConvexShape& shape, std::vector<sf::Vector2f> const& points);
	void assignPackmanShape(sf::ConvexShape& topShape, sf::ConvexShape& bottomShape, const float phaseAnimation);

	void initializePackman(Packman& packman);

	void updateHeroDirection(Packman& packman);
	void updateHero(Packman& packman, float elapsedTime, Field& field, const float speed);
	void drawPackman(sf::RenderWindow& window, const Packman& packman);

	sf::FloatRect getPackmanBounds(const Packman& packman);
};