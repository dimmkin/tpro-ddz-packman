#include "packman.h"
#include "field.h"

void Packman::updateHeroDirection(Packman& packman)
{
	packman.direction = Direction::NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		packman.direction = Direction::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		packman.direction = Direction::DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		packman.direction = Direction::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		packman.direction = Direction::RIGHT;
	}
}

void Packman::updateHero(Packman& packman, float elapsedTime, Field& field, const float speed)
{
	const float step = speed * elapsedTime;

	updateHeroDirection(packman);

	sf::Vector2f movement(0.f, 0.f);
	movement = buildMovement(movement, packman, step);
	
	const sf::FloatRect packmanBounds = packman.figure.getGlobalBounds();
	if (checkFieldWallsCollision(field, packmanBounds, movement, speed)) {
		packman.direction = Direction::NONE;
	}

	packman.MovingOut(field, packman, movement, speed);

	packman.eatenCookies += eatAllCookiesBounds(field, packman.figure.getGlobalBounds());

	packman.figure.move(movement);
}
