#pragma once
#include "menu.h"

namespace game {

	class Maps
	{
		double __menuX;
		double __menuY;
		int __mapsStep;
		int __maxMaps;
		int __sizeFont;
		int __mainMapsSelected;
		sf::Font __font;

		sf::Text* __mainMaps;
		sf::Color __mapsTextColor = sf::Color::Blue;
		sf::Color __choseTextColor = sf::Color::Yellow;
		sf::Color __borderColor = sf::Color::Blue;

		void setInitTextMaps(sf::Text& text, sf::String str, double xpos, double ypos);

		sf::RenderWindow& __window;
	public:
		Maps(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~Maps()
		{
			delete[] __mainMaps;
		}

		void draw();

		void MoveLeft();

		void MoveRight();

		void setColorTextMaps(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignMaps(int posx);

		int getMapsNumber()
		{
			return __mainMapsSelected;
		}
	};
}