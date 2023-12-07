#include "menuBase.h"

game::Pause::Pause(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
{}