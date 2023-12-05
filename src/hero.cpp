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

void Hero::updateHeroDirection()
{
	if (direction == Direction::UP) {
		direction = randomDirection(Direction::UP);
		return;
	}
	if (direction == Direction::DOWN) {
		direction = randomDirection(Direction::DOWN);
		return;
	}
	if (direction == Direction::LEFT) {
		direction = randomDirection(Direction::LEFT);
		return;
	}
	if (direction == Direction::RIGHT) {
		direction = randomDirection(Direction::RIGHT);
		return;
	}
	if (direction == Direction::NONE) {
		direction = Direction::UP;
		return;
	}
}

bool Hero::initializeHero(const sf::Vector2f& position, const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath))
		return false;

	direction = Direction::NONE;
	figure.setSize({ 40.f, 40.f });
	figure.setPosition(position);
	figure.setTexture(&texture);
	figure.setTextureRect(FRAME_EYES_TOP);

	return true;
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

void Hero::MovingOut(Field& field, sf::Vector2f& movement, const float speed)
{
	if (figure.getPosition().x < LEFT_INDENTATION) {
		figure.setPosition(figure.getPosition().x + field.width * BLOCK_SIZE - 35, figure.getPosition().y);
	}
	else if (figure.getPosition().x > LEFT_INDENTATION - 35 + field.width * BLOCK_SIZE) {
		figure.setPosition(LEFT_INDENTATION, figure.getPosition().y);
	}
	if (figure.getPosition().y < TOP_INDENTATION) {
		figure.setPosition(figure.getPosition().x, figure.getPosition().y + field.width * BLOCK_SIZE - TOP_INDENTATION);
	}
	else if (figure.getPosition().y > field.width * BLOCK_SIZE) {
		figure.setPosition(figure.getPosition().x, TOP_INDENTATION);
	}
}

void Hero::drawEyes()
{
	if (direction == Direction::LEFT) {
		figure.setTextureRect(FRAME_EYES_LEFT);
		return;
	}
	if (direction == Direction::RIGHT) {
		figure.setTextureRect(FRAME_EYES_RIGHT);
		return;
	}
	if (direction == Direction::DOWN) {
		figure.setTextureRect(FRAME_EYES_BOTTOM);
		return;
	}
	if (direction == Direction::UP) {
		figure.setTextureRect(FRAME_EYES_TOP);
		return;
	}
	if (direction == Direction::NONE) {
		figure.setTextureRect(FRAME_EYES_TOP);
		return;
	}
}

void Hero::updateHero(float elapsedTime, Field& field, const float speed)
{
	const float step = speed * elapsedTime;

	sf::Vector2f movement(0.f, 0.f);

	movement = buildMovement(movement, *this, step);

	if (direction == Direction::NONE)
		updateHeroDirection();

	static std::chrono::steady_clock::time_point lastDirectionChangeTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::seconds elapsedTimeSinceLastChange = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastDirectionChangeTime);

	const sf::FloatRect heroBounds = figure.getGlobalBounds();
	if (field.checkFieldWallsCollision(heroBounds, movement, speed) || elapsedTimeSinceLastChange.count() >= 0.01) {
		updateHeroDirection();
		lastDirectionChangeTime = std::chrono::steady_clock::now();
	}

	MovingOut(field, movement, speed);
	figure.move(movement);

	drawEyes();
}

void Hero::drawHero(sf::RenderWindow& window)
{
	window.draw(figure);
}