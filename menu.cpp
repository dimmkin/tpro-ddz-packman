#include "menu.h"

void game::Menu::setInitTextMenu(sf::Text& text, sf::String str, double xpos, double ypos)
{
	text.setFont(__font);
	text.setFillColor(__menuTextColor);
	text.setString(str);
	text.setCharacterSize(__sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(__borderColor);
}

void game::Menu::AlignMenu(int posx)
{
	double nullx = 0;
	for (int i = 0; i < __maxMenu; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = __mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = nullx = __mainMenu[i].getLocalBounds().width / 2;
			break;
		}
		__mainMenu[i].setPosition(__mainMenu[i].getPosition().x - nullx, __mainMenu[i].getPosition().y);
	}

}

game::Menu::Menu(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __menuStep(step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxMenu = index;
	__mainMenu = new sf::Text[__maxMenu];
	
	for (int i = 0, ypos = __menuY; i < __maxMenu; i++, ypos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], __menuX, ypos);
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

void game::Menu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	__menuTextColor = menColor;
	__choseTextColor = ChoColor;
	__borderColor = BordColor;

	for (int i = 0; i < __maxMenu; i++) {
		__mainMenu[i].setFillColor(__menuTextColor);
		__mainMenu[i].setOutlineColor(__borderColor);
	}

	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
}