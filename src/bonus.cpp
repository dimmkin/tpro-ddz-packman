#include "bonus.h"
#include "field.h"
#include "packman.h"

bool Bonus::initializeBonus(const sf::Vector2f& position, const std::string& texturePath, const sf::IntRect frame, TypesBonuses type, bool active)
{
	if (!texture.loadFromFile(texturePath))
		return false;

	bonusType = type;
	figure.setSize({ 40.f, 40.f });
	figure.setPosition(position);
	figure.setTexture(&texture);
	figure.setTextureRect(frame);
	active = false;

	return true;
}

void Bonus::drawBonus(sf::RenderWindow& window)
{
	window.draw(figure);
}
