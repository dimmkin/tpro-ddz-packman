#include "hero.h"
#include "field.h"

void Hero::updateHeroDirection(Hero& hero)
{
	if (hero.direction == Direction::UP) {
		hero.direction = Direction::RIGHT;
		return;
	}
	if (hero.direction == Direction::DOWN) {
		hero.direction = Direction::LEFT;
		return;
	}
	if (hero.direction == Direction::LEFT) {
		hero.direction = Direction::UP;
		return;
	}
	if (hero.direction == Direction::RIGHT) {
		hero.direction = Direction::DOWN;
		return;
	}
	if (hero.direction == Direction::NONE) {
		hero.direction = Direction::LEFT;
		return;
	}
}

void Hero::initializeHero(Hero& hero, const sf::Vector2f& position, const float radius, const sf::Color color)
{
	hero.direction = Direction::NONE;
	hero.figure.setRadius(radius);
	hero.figure.setFillColor(color);
	hero.figure.setPosition(position);
}

sf::Vector2f Hero::buildMovement(sf::Vector2f& movement, Hero& hero, const float step)
{
	if (hero.direction == Direction::UP) {
		movement.y -= step;
	}
	if (hero.direction == Direction::DOWN) {
		movement.y += step;
	}
	if (hero.direction == Direction::LEFT) {
		movement.x -= step;
	}
	if (hero.direction == Direction::RIGHT) {
		movement.x += step;
	}
	return movement;
}

void Hero::collisionsAndMovingOut(Field& field, Hero& hero, sf::Vector2f& movement, const float speed)

{
	const sf::FloatRect heroBounds = hero.figure.getGlobalBounds();
	if (checkFieldWallsCollision(field, heroBounds, movement, speed)) {
		hero.updateHeroDirection(hero);
	}
	if (hero.figure.getPosition().x < 535) {
		hero.figure.setPosition(hero.figure.getPosition().x + field.width * BLOCK_SIZE - 35, hero.figure.getPosition().y);
	}
	else if (hero.figure.getPosition().x > 500 + field.width * BLOCK_SIZE) {
		hero.figure.setPosition(535, hero.figure.getPosition().y);
	}
}

void Hero::updateHero(Hero& hero, float elapsedTime, Field& field, const float speed)
{
	const float step = speed * elapsedTime;

	sf::Vector2f movement(0.f, 0.f);

	movement = buildMovement(movement, hero, step);

	if (hero.direction == Direction::NONE) {
		hero.updateHeroDirection(hero);
	}

	hero.collisionsAndMovingOut(field, hero, movement, speed);

	hero.figure.move(movement);
}

void Hero::drawHero(sf::RenderWindow& window, const Hero& hero)
{
	window.draw(hero.figure);
}
