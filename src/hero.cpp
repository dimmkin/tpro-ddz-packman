#include "../include/hero.h"
#include "../include/field.h"

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

void Hero::updateHeroDirection()
{
	if (__direction == Direction::UP) {
		__direction = randomDirection(Direction::UP);
		return;
	}
	if (__direction == Direction::DOWN) {
		__direction = randomDirection(Direction::DOWN);
		return;
	}
	if (__direction == Direction::LEFT) {
		__direction = randomDirection(Direction::LEFT);
		return;
	}
	if (__direction == Direction::RIGHT) {
		__direction = randomDirection(Direction::RIGHT);
		return;
	}
	if (__direction == Direction::NONE) {
		__direction = Direction::UP;
		return;
	}
}
Direction Hero::changeOfDirectionGost(Direction gost, Direction Packman)
{
	if(Packman == Direction::RIGHT && gost == Direction::LEFT) {
		return Direction::RIGHT;
	}
	if(Packman == Direction::LEFT && gost == Direction::RIGHT) {
		return Direction::LEFT;
	}
	if(Packman == Direction::UP && gost == Direction::DOWN) {
		return Direction::UP;
	}
	if(Packman == Direction::DOWN && gost == Direction::UP) {
		return Direction::DOWN;
	}
}

Direction Hero::changeOfDirection(Direction direction)
{
	if (direction == Direction::UP) {
		direction =Direction::DOWN;
		return Direction::DOWN;
	}
	if (direction == Direction::DOWN) {
		direction = Direction::UP;
		return Direction::UP;
	}
	if (direction == Direction::LEFT) {
		direction = Direction::RIGHT;
		return Direction::RIGHT;
	}
	if (direction == Direction::RIGHT) {
		direction = Direction::LEFT;
		return Direction::LEFT;
	}
	if (direction == Direction::NONE) {
		direction = Direction::UP;
		return Direction::UP;
	}
}

bool Hero::initializeHero(const sf::Vector2f& position, const std::string& texturePath)
{
	if (!__texture.loadFromFile(texturePath))
		return false;

	__direction = Direction::NONE;
	__figure.setSize({ 40.f, 40.f });
	__figure.setPosition(position);
	__figure.setTexture(&__texture);
	__figure.setTextureRect(FRAME_EYES_TOP);

	return true;
}

sf::Vector2f Hero::buildMovement(sf::Vector2f& movement, Hero& hero, const float step)
{
	if (hero.__direction == Direction::UP) {
		movement.y -= step;
	}
	if (hero.__direction == Direction::DOWN) {
		movement.y += step;
	}
	if (hero.__direction == Direction::LEFT) {
		movement.x -= step;
	}
	if (hero.__direction == Direction::RIGHT) {
		movement.x += step;
	}
	return movement;
}

void Hero::MovingOut(Field& field, sf::Vector2f& movement, const float speed)
{
	if (__figure.getPosition().x < LEFT_INDENTATION) {
		__figure.setPosition(__figure.getPosition().x + field.__width * BLOCK_SIZE - 35, __figure.getPosition().y);
	}
	else if (__figure.getPosition().x > LEFT_INDENTATION - 35 + field.__width * BLOCK_SIZE) {
		__figure.setPosition(LEFT_INDENTATION, __figure.getPosition().y);
	}
	if (__figure.getPosition().y < TOP_INDENTATION) {
		__figure.setPosition(__figure.getPosition().x, __figure.getPosition().y + field.__width * BLOCK_SIZE - TOP_INDENTATION);
	}
	else if (__figure.getPosition().y > field.__width * BLOCK_SIZE) {
		__figure.setPosition(__figure.getPosition().x, TOP_INDENTATION);
	}
}

void Hero::drawEyes()
{
	if (__direction == Direction::LEFT) {
		__figure.setTextureRect(FRAME_EYES_LEFT);
		return;
	}
	if (__direction == Direction::RIGHT) {
		__figure.setTextureRect(FRAME_EYES_RIGHT);
		return;
	}
	if (__direction == Direction::DOWN) {
		__figure.setTextureRect(FRAME_EYES_BOTTOM);
		return;
	}
	if (__direction == Direction::UP) {
		__figure.setTextureRect(FRAME_EYES_TOP);
		return;
	}
	if (__direction == Direction::NONE) {
		__figure.setTextureRect(FRAME_EYES_TOP);
		return;
	}
}

void Hero::updateHero(float elapsedTime, Field& field, const float speed, bool stop)
{
	const float step = (stop) ? 0 : speed * elapsedTime;
	const float localspeed = (stop) ? 0 : speed;

	sf::Vector2f movement(0.f, 0.f);

	movement = buildMovement(movement, *this, step);

	if (__direction == Direction::NONE)
		updateHeroDirection();

	static std::chrono::steady_clock::time_point lastDirectionChangeTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::seconds elapsedTimeSinceLastChange = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastDirectionChangeTime);

	const sf::FloatRect heroBounds = __figure.getGlobalBounds();

	if (field.checkFieldWallsCollision(heroBounds, movement, localspeed) || elapsedTimeSinceLastChange.count() >= 0.01) {
		updateHeroDirection();
		lastDirectionChangeTime = std::chrono::steady_clock::now();
	}

	MovingOut(field, movement, localspeed);

	__figure.move(movement);

	drawEyes();
}

void Hero::drawHero(sf::RenderWindow& window)
{
	window.draw(__figure);
}