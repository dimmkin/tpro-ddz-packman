#include "menu.h"

game::Menu::Menu(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __menuStep(step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxMenu = index;
	__mainMenu = new sf::Text[__maxMenu];
	
	for (int i = 0, ypos = __menuY; i < __maxMenu; i++, ypos += __menuStep) setInitText(__mainMenu[i], name[i], __menuX, ypos);
	__mainMenuSelected = 0;
	
	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
}

void game::Menu::MoveUp()
{
	__mainMenuSelected--;
	
	if (__mainMenuSelected >= 0) {
		__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
		__mainMenu[__mainMenuSelected + 1].setFillColor(__menuTextColor);
	}
	else
	{
		__mainMenu[0].setFillColor(__menuTextColor);
		__mainMenuSelected = __maxMenu - 1;
		__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
	}
}

void game::Menu::MoveDown()
{
	__mainMenuSelected++;
	
	if (__mainMenuSelected < __maxMenu) {
		__mainMenu[__mainMenuSelected - 1].setFillColor(__menuTextColor);
		__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
	}
	else
	{
		__mainMenu[__maxMenu - 1].setFillColor(__menuTextColor);
		__mainMenuSelected = 0;
		__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
	}

}

void game::Menu::draw()
{
		
	for (int i = 0; i < __maxMenu; i++) __window.draw(__mainMenu[i]);
}