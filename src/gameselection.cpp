#include "menuBase.h"

game::GameSelection::GameSelection(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxMenu = index;
	__mainMenu = new sf::Text[__maxMenu];

	for (int i = 0, xpos = __menuX; i < __maxMenu; i++, xpos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], xpos, __menuY);
	__mainMenuSelected = 0;

	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
}