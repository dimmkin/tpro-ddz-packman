/**
 * @file menu.cpp
 */

#include "../include/menuBase.h"

game::Menu::Menu(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
{}