#include "packman.h"
#include "field.h"

sf::Vector2f Packman::getRadialPoint(float angle, float radius)
{
	const float radians = ((angle - PHASE) * NUMBER_PI / PI_RADIAN);
	return radius * sf::Vector2f(std::cos(radians), std::sin(radians));
}

void Packman::assignFigure(sf::ConvexShape& shape, std::vector<sf::Vector2f> const& points)
{
	const unsigned int pointCount = unsigned(points.size());
	shape.setPointCount(pointCount);
	for (size_t i = 0; i < pointCount; ++i) {
		shape.setPoint(i, points[i]);
	}
}

void Packman::assignPackmanFigure(sf::ConvexShape& topShape, sf::ConvexShape& bottomShape, const float phaseAnimation)
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
	assignFigure(topShape, points);
	points.clear();

	for (float angle = 180.f; angle <= 360 - angleDeviation; angle += 5.f) {
		points.push_back(getRadialPoint(angle, radius));
	}
	points.push_back(center);
	assignFigure(bottomShape, points);
}

void Packman::updateHeroDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direction = Direction::UP;
		orientationDegrees = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		direction = Direction::DOWN;
		orientationDegrees = 180;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction = Direction::LEFT;
		orientationDegrees = 270;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction = Direction::RIGHT;
		orientationDegrees = 90;
	}
}

int Packman::directionOrientationDegrees(Direction direction) {
	if (direction == Direction::UP) {
		return 0;
	}
	else if (direction == Direction::DOWN) {
		return 180;
	}
	if (direction == Direction::LEFT) {
		return 270;
	}
	else if (direction == Direction::RIGHT) {
		return 90;
	}
}

void Packman::initializePackman(Field& field, Packman& packman, float speed)
{
	packman.direction = Direction::NONE;
	packman.position = field.getPackmanStartPosition();
	packman.eatenCookies = 0;
	packman.orientationDegrees = 90;
	packman.phaseAnimation = 0;
	packman.speed = speed;

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	int i = data["Option"][3];
	sf::Color color_pacman;
	switch (i)
	{
	case 1:
		color_pacman = sf::Color::Red;
		break;
	case 2:
		color_pacman = sf::Color::Magenta;
		break;
	case 3:
		color_pacman = sf::Color::Green;
		break;
	default:
		break;
	}
	packman.topShape.setFillColor(color_pacman);
	packman.bottomShape.setFillColor(color_pacman);
}

void Packman::setSpeedMultiplier(float newSpeed)
{
	speed = newSpeed;
}

void Packman::updateHero(float elapsedTime, Field& field)
{
	const float step = speed * elapsedTime;

	updateHeroDirection();

	sf::Vector2f movement(0.f, 0.f);
	movement = buildMovement(movement, *this, step);

	const sf::FloatRect packmanBounds = getPackmanBounds();
	if (field.checkFieldWallsCollision(packmanBounds, movement, speed)) {
	}
	if (position.x < LEFT_INDENTATION) {
		position.x = this->position.x + field.width * BLOCK_SIZE - 35;
	}
	else if (position.x > LEFT_INDENTATION - 35 + field.width * BLOCK_SIZE) {
		position.x = LEFT_INDENTATION;
	}
	if (position.y < TOP_INDENTATION) {
		position.y = position.y + field.width * BLOCK_SIZE - TOP_INDENTATION;
	}
	else if (position.y > field.width * BLOCK_SIZE) {
		position.y = TOP_INDENTATION;
	}

	eatenCookies += field.eatAllCookiesBounds(getPackmanBounds());

	position += movement;

	if (this->direction == Direction::NONE) {
		this->phaseAnimation = 0;
	}
	else {
		const float deltaPhase = elapsedTime / 0.3f;
		this->phaseAnimation = (this->phaseAnimation + deltaPhase) - static_cast<int>(phaseAnimation + deltaPhase);
	}
	assignPackmanFigure(topShape, bottomShape, phaseAnimation);
}

void Packman::drawPackman(sf::RenderWindow& window)
{
	sf::RenderStates states;

	states.transform.translate(position);

	states.transform.rotate(orientationDegrees);

	window.draw(topShape, states);
	window.draw(bottomShape, states);
}

sf::FloatRect Packman::getPackmanBounds()
{
	return sf::FloatRect(position.x - RADIUS_OF_PACKMAN, position.y - RADIUS_OF_PACKMAN, 2.f * RADIUS_OF_PACKMAN, 2.f * RADIUS_OF_PACKMAN);
}
