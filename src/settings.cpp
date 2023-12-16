/**
 * @file settings.cpp
 */

#include "../include/menuBase.h"

game::Settings::Settings(sf::RenderWindow& window, double settingsmenux, double settingsy,
	int index, sf::String name[], int sizeFont, int step)
	: MenuBase(window, settingsmenux, settingsy, index, name, sizeFont, step)
{
	__maxMenu = index;
	__mainMenu = new sf::Text[__maxMenu];

	for (int i = 0, xpos = __menuX; i < __maxMenu; i++, xpos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], xpos, __menuY);
	__mainMenuSelected = 0;

	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
}