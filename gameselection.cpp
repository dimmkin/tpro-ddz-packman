#include "gameselection.h"

void game::GameSelection::setInitTextGameSelection(sf::Text& text, sf::String str, double xpos, double ypos)
{
	text.setFont(__font);
	text.setFillColor(__gameSelectionTextColor);
	text.setString(str);
	text.setCharacterSize(__sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(__borderColor);
}

void game::GameSelection::AlignGameSelection(int posx)
{
	double nullx = 0;
	for (int i = 0; i < __maxGameSelection; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = __mainGameSelection[i].getLocalBounds().width;
			break;
		case 2:
			nullx = nullx = __mainGameSelection[i].getLocalBounds().width / 2;
			break;
		}
		__mainGameSelection[i].setPosition(__mainGameSelection[i].getPosition().x - nullx, __mainGameSelection[i].getPosition().y);
	}

}

game::GameSelection::GameSelection(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __gameSelectionStep(step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxGameSelection = index;
	__mainGameSelection = new sf::Text[__maxGameSelection];

	for (int i = 0, xpos = __menuX; i < __maxGameSelection; i++, xpos += __gameSelectionStep + 200) setInitTextGameSelection(__mainGameSelection[i], name[i], xpos, __menuY);
	__mainGameSelected = 0;

	__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
}

void game::GameSelection::draw()
{
	for (int i = 0; i < __maxGameSelection; i++) __window.draw(__mainGameSelection[i]);
}

void game::GameSelection::MoveLeft()
{
	__mainGameSelected--;

	if (__mainGameSelected >= 0) {
		__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
		__mainGameSelection[__mainGameSelected + 1].setFillColor(__gameSelectionTextColor);
	}
	else
	{
		__mainGameSelection[0].setFillColor(__gameSelectionTextColor);
		__mainGameSelected = __maxGameSelection - 1;
		__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
	}
}

void game::GameSelection::MoveRight()
{
	__mainGameSelected++;

	if (__mainGameSelected < __maxGameSelection) {
		__mainGameSelection[__mainGameSelected - 1].setFillColor(__gameSelectionTextColor);
		__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
	}
	else
	{
		__mainGameSelection[__maxGameSelection - 1].setFillColor(__gameSelectionTextColor);
		__mainGameSelected = 0;
		__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
	}
}

void game::GameSelection::setColorTextGameSelection(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	__gameSelectionTextColor = menColor;
	__choseTextColor = ChoColor;
	__borderColor = BordColor;

	for (int i = 0; i < __maxGameSelection; i++) {
		__mainGameSelection[i].setFillColor(__gameSelectionTextColor);
		__mainGameSelection[i].setOutlineColor(__borderColor);
	}

	__mainGameSelection[__mainGameSelected].setFillColor(__choseTextColor);
}