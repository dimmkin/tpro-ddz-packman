#include "packman.h"
#include "field.h"

sf::Vector2f Packman::getRadialPoint(float angle, float radius)
{
	const float radians = ((angle - 90) * 3.141592654f / 180);

	return radius * sf::Vector2f(std::cos(radians), std::sin(radians));
}

void Packman::assignShape(sf::ConvexShape& shape, std::vector<sf::Vector2f> const& points)
{
	const unsigned int pointCount = unsigned(points.size());
	shape.setPointCount(pointCount);
	for (size_t i = 0; i < pointCount; ++i) {
		shape.setPoint(i, points[i]);
	}
}

void Packman::assignPackmanShape(sf::ConvexShape& topShape, sf::ConvexShape& bottomShape, const float phaseAnimation)
{
	const float phaseDeviation = 2.f * fabsf(0.5f - phaseAnimation);
	const float angleDeviation = 0.5 * phaseDeviation * 100.f;

	const float radius = 12.0f;
	std::vector<sf::Vector2f> points;
	sf::Vector2f center(0, 0.25f * radius);

	for (float angle = 180.f; angle >= angleDeviation; angle -= 5.f) {
		points.push_back(getRadialPoint(angle, radius));
	}
	points.push_back(center);
	assignShape(topShape, points);
	points.clear();

	for (float angle = 180.f; angle <= 360 - angleDeviation; angle += 5.f) {
		points.push_back(getRadialPoint(angle, radius));
	}
	points.push_back(center);
	assignShape(bottomShape, points);
}

void Packman::updateHeroDirection(Packman& packman)
{
	packman.direction = Direction::NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		packman.direction = Direction::UP;
		packman.orientationDegrees = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		packman.direction = Direction::DOWN;
		packman.orientationDegrees = 180;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		packman.direction = Direction::LEFT;
		packman.orientationDegrees = 270;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		packman.direction = Direction::RIGHT;
		packman.orientationDegrees = 90;
	}
}

void Packman::initializePackman(Packman& packman)
{
	packman.direction = Direction::NONE;
	packman.position = getPackmanStartPosition();
	packman.eatenCookies = 0;
	packman.orientationDegrees = 90;
	packman.phaseAnimation = 0;
	
	packman.topShape.setFillColor(sf::Color::Yellow);
	packman.bottomShape.setFillColor(sf::Color::Yellow);
}

void Packman::updateHero(Packman& packman, float elapsedTime, Field& field, const float speed)
{
	const float step = speed * elapsedTime;

	updateHeroDirection(packman);

	sf::Vector2f movement(0.f, 0.f);
	movement = buildMovement(movement, packman, step);
	
	const sf::FloatRect packmanBounds = getPackmanBounds(packman);
	if (checkFieldWallsCollision(field, packmanBounds, movement, speed)) {
		packman.direction = Direction::NONE;
	}
	if (packman.position.x < 535) {
		packman.position.x = packman.position.x + field.width * BLOCK_SIZE - 35;
	}
	else if (packman.position.x > 500 + field.width * BLOCK_SIZE) {
		packman.position.x = 535;
	}
	if (packman.position.y < 190) {
		packman.position.y = packman.position.y + field.width * BLOCK_SIZE - 190;
	}
	else if (packman.position.y > field.width * BLOCK_SIZE) {
		packman.position.y = 190;
	}
	
	packman.eatenCookies += eatAllCookiesBounds(field, getPackmanBounds(packman));
	packman.position += movement;

	if (packman.direction == Direction::NONE) {
		packman.phaseAnimation = 0;
	}
	else {
		const float deltaPhase = elapsedTime / 0.3f;
		packman.phaseAnimation = fmodf(packman.phaseAnimation + deltaPhase, 1.f);
	}
	assignPackmanShape(packman.topShape, packman.bottomShape, packman.phaseAnimation);
}

void Packman::drawPackman(sf::RenderWindow& window, const Packman& packman)
{
	sf::RenderStates states;

	states.transform.translate(packman.position);

	states.transform.rotate(packman.orientationDegrees);

	window.draw(packman.topShape, states);
	window.draw(packman.bottomShape, states);
}

sf::FloatRect Packman::getPackmanBounds(const Packman& packman)
{
	return sf::FloatRect(packman.position.x - 20.f,
		packman.position.y - 20.f,
		2.f * 20.f,
		2.f * 20.f);
}
