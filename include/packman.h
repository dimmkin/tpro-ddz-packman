#pragma once

#include <SFML/Graphics.hpp>
#include "hero.h"

class Packman : public Hero
{
public:
	unsigned int eatenCookies;

	void updateHeroDirection(Packman& packman);
	void updateHero(Packman& packman, float elapsedTime, Field& field, const float speed);
};