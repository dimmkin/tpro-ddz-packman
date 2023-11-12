#include "bots.h"

void game::Bots::setInitTextBots(sf::Text& text, sf::String str, double xpos, double ypos)
{
	text.setFont(__font);
	text.setFillColor(__botsTextColor);
	text.setString(str);
	text.setCharacterSize(__sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(__borderColor);
}

void game::Bots::AlignBots(int posx)
{
	double nullx = 0;
	for (int i = 0; i < __maxBots; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = __mainBots[i].getLocalBounds().width;
			break;
		case 2:
			nullx = nullx = __mainBots[i].getLocalBounds().width / 2;
			break;
		}
		__mainBots[i].setPosition(__mainBots[i].getPosition().x - nullx, __mainBots[i].getPosition().y);
	}

}

game::Bots::Bots(sf::RenderWindow& window, double menux, double menuy,
	int index, sf::String name[], int sizeFont, int step)
	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __botsStep(step)
{
	if (!__font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) exit(32);
	__maxBots = index;
	__mainBots = new sf::Text[__maxBots];

	for (int i = 0, xpos = __menuX; i < __maxBots; i++, xpos += __botsStep + 50) setInitTextBots(__mainBots[i], name[i], xpos, __menuY);
	__mainBotsSelected = 0;

	__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
}

void game::Bots::MoveLeft()
{
	__mainBotsSelected--;

	if (__mainBotsSelected >= 0) {
		__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
		__mainBots[__mainBotsSelected + 1].setFillColor(__botsTextColor);
	}
	else
	{
		__mainBots[0].setFillColor(__botsTextColor);
		__mainBotsSelected = __maxBots - 1;
		__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
	}
}

void game::Bots::MoveRight()
{
	__mainBotsSelected++;

	if (__mainBotsSelected < __maxBots) {
		__mainBots[__mainBotsSelected - 1].setFillColor(__botsTextColor);
		__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
	}
	else
	{
		__mainBots[__maxBots - 1].setFillColor(__botsTextColor);
		__mainBotsSelected = 0;
		__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
	}

}

void game::Bots::draw()
{
	for (int i = 0; i < __maxBots; i++) __window.draw(__mainBots[i]);
}

void game::Bots::setColorTextBots(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	__botsTextColor = menColor;
	__choseTextColor = ChoColor;
	__borderColor = BordColor;

	for (int i = 0; i < __maxBots; i++) {
		__mainBots[i].setFillColor(__botsTextColor);
		__mainBots[i].setOutlineColor(__borderColor);
	}

	__mainBots[__mainBotsSelected].setFillColor(__choseTextColor);
}