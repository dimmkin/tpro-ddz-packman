/**
 * @file bots.cpp
 */

#include "../include/menuBase.h"

game::ChoseBots::ChoseBots(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	: GameSelection(window, menux, menuy, index, name, sizeFont, step)
{}