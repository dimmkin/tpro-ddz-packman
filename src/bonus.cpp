#include "../include/bonus.h"
#include "../include/field.h"
#include "../include/packman.h"

bool Bonus::initializeBonus(const sf::Vector2f& position, const std::string& texturePath, const sf::IntRect frame, TypesBonuses type, bool active)
{
	if (!__texture.loadFromFile(texturePath))
		return false;

	__bonusType = type;
	__figure.setSize({ 40.f, 40.f });
	__figure.setPosition(position);
	__figure.setTexture(&__texture);
	__figure.setTextureRect(frame);
	__active = false;

	return true;
}

void Bonus::drawBonus(sf::RenderWindow& window)
{
	window.draw(__figure);
}
