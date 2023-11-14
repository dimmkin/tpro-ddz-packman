#include "menuBase.h"

game::Settigns::Settigns(sf::RenderWindow& window, double settignsmenux, double settignsy,
	int index, sf::String name[], int sizeFont, int step)
	: MenuBase(window, settignsmenux, settignsy, index, name, sizeFont, step)
{
	if (!__font.loadFromFile("font/EightBits.ttf")) exit(32);
	__maxMenu = index;
	__mainMenu = new sf::Text[__maxMenu];

	for (int i = 0, xpos = __menuX; i < __maxMenu; i++, xpos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], xpos, __menuY);
	__mainMenuSelected = 0;

	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
}