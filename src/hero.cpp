#include "hero.h"
#include "field.h"

Direction Hero::randomDirection(Direction previousDirection)
{
	constexpr std::array<Direction, 4> directionValues{ { Direction::UP,Direction::DOWN,Direction::LEFT,Direction::RIGHT } };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, directionValues.size() - 1);
	int randomIndex = dis(gen);
	Direction randomDirection = directionValues[randomIndex];

	while (randomDirection == previousDirection) {
		randomIndex = dis(gen);
		randomDirection = directionValues[randomIndex];
	}

	return randomDirection;
}

void Hero::updateHeroDirection(Hero& hero)
{
	if (hero.direction == Direction::UP) {
		hero.direction = randomDirection(Direction::UP);
		return;
	}
	if (hero.direction == Direction::DOWN) {
		hero.direction = randomDirection(Direction::DOWN);
		return;
	}
	if (hero.direction == Direction::LEFT) {
		hero.direction = randomDirection(Direction::LEFT);
		return;
	}
	if (hero.direction == Direction::RIGHT) {
		hero.direction = randomDirection(Direction::RIGHT);
		return;
	}
	if (hero.direction == Direction::NONE) {
		hero.direction = Direction::UP;
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

void Hero::MovingOut(Field& field, Hero& hero, sf::Vector2f& movement, const float speed)
{
	if (hero.figure.getPosition().x < 535) {
		hero.figure.setPosition(hero.figure.getPosition().x + field.width * BLOCK_SIZE - 35, hero.figure.getPosition().y);
	}
	else if (hero.figure.getPosition().x > 500 + field.width * BLOCK_SIZE) {
		hero.figure.setPosition(535, hero.figure.getPosition().y);
	}
	if (hero.figure.getPosition().y < 190) {
		hero.figure.setPosition(hero.figure.getPosition().x, hero.figure.getPosition().y + field.width * BLOCK_SIZE - 190);
	}
	else if (hero.figure.getPosition().y > field.width * BLOCK_SIZE) {
		hero.figure.setPosition(hero.figure.getPosition().x, 190);
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

	static std::chrono::steady_clock::time_point lastDirectionChangeTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::seconds elapsedTimeSinceLastChange = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastDirectionChangeTime);
	
	const sf::FloatRect heroBounds = hero.figure.getGlobalBounds();
	if (checkFieldWallsCollision(field, heroBounds, movement, speed) || elapsedTimeSinceLastChange.count() >= 0.01) {
		updateHeroDirection(hero);
		lastDirectionChangeTime = std::chrono::steady_clock::now();
	}

	hero.MovingOut(field, hero, movement, speed);

	hero.figure.move(movement);
}

void Hero::drawHero(sf::RenderWindow& window, const Hero& hero)
{
	window.draw(hero.figure);
}
