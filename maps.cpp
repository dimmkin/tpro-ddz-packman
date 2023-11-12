#include "maps.h"

void game::Maps::setInitTextMaps(sf::Text& text, sf::String str, double xpos, double ypos)
{
	text.setFont(__font);
	text.setFillColor(__mapsTextColor);
	text.setString(str);
	text.setCharacterSize(__sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(__borderColor);
}

void game::Maps::AlignMaps(int posx)
{
	double nullx = 0;
	for (int i = 0; i < __maxMaps; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = __mainMaps[i].getLocalBounds().width;
			break;
		case 2:
			nullx = nullx = __mainMaps[i].getLocalBounds().width / 2;
			break;
		}
		__mainMaps[i].setPosition(__mainMaps[i].getPosition().x - nullx, __mainMaps[i].getPosition().y);
	}
}

game::Maps::Maps(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __mapsStep(step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxMaps = index;
	__mainMaps = new sf::Text[__maxMaps];

	for (int i = 0, xpos = __menuX; i < __maxMaps; i++, xpos += __mapsStep + 300) setInitTextMaps(__mainMaps[i], name[i], xpos, __menuY);
	__mainMapsSelected = 0;

	__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
}

void game::Maps::MoveLeft()
{
	__mainMapsSelected--;

	if (__mainMapsSelected >= 0) {
		__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
		__mainMaps[__mainMapsSelected + 1].setFillColor(__mapsTextColor);
	}
	else
	{
		__mainMaps[0].setFillColor(__mapsTextColor);
		__mainMapsSelected = __maxMaps - 1;
		__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
	}
}

void game::Maps::MoveRight()
{
	__mainMapsSelected++;

	if (__mainMapsSelected < __maxMaps) {
		__mainMaps[__mainMapsSelected - 1].setFillColor(__mapsTextColor);
		__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
	}
	else
	{
		__mainMaps[__maxMaps - 1].setFillColor(__mapsTextColor);
		__mainMapsSelected = 0;
		__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
	}

}

void game::Maps::draw()
{
	for (int i = 0; i < __maxMaps; i++) __window.draw(__mainMaps[i]);
}

void game::Maps::setColorTextMaps(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	__mapsTextColor = menColor;
	__choseTextColor = ChoColor;
	__borderColor = BordColor;

	for (int i = 0; i < __maxMaps; i++) {
		__mainMaps[i].setFillColor(__mapsTextColor);
		__mainMaps[i].setOutlineColor(__borderColor);
	}

	__mainMaps[__mainMapsSelected].setFillColor(__choseTextColor);
}