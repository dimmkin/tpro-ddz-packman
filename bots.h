#pragma once
#include "menu.h"

namespace game {
	
	class Bots
	{
		double __menuX;
		double __menuY;
		int __botsStep;
		int __maxBots;
		int __sizeFont;
		int __mainBotsSelected;
		sf::Font __font;

		sf::Text* __mainBots;
		sf::Color __botsTextColor = sf::Color::Blue;
		sf::Color __choseTextColor = sf::Color::Yellow;
		sf::Color __borderColor = sf::Color::Blue;

		void setInitTextBots(sf::Text& text, sf::String str, double xpos, double ypos);

		sf::RenderWindow& __window;
	public:
		Bots(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~Bots()
		{
			delete[] __mainBots;
		}

		void draw();

		void MoveLeft();

		void MoveRight();

		void setColorTextBots(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignBots(int posx);

		int getBotsNumber()
		{
			return __mainBotsSelected;
		}
	};
}