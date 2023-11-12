#pragma once
#include "menu.h"

namespace game {
	
	class GameSelection
	{
		double __menuX;
		double __menuY;
		int __gameSelectionStep;
		int __maxGameSelection;
		int __sizeFont;
		int __mainGameSelected;
		sf::Font __font;

		sf::Text* __mainGameSelection;
		sf::Color __gameSelectionTextColor = sf::Color::Blue;
		sf::Color __choseTextColor = sf::Color::Yellow;
		sf::Color __borderColor = sf::Color::Blue;

		void setInitTextGameSelection(sf::Text& text, sf::String str, double xpos, double ypos);

		sf::RenderWindow& __window;

	public:
		GameSelection(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~GameSelection()
		{
			delete[] __mainGameSelection;
		}

		void draw();

		void MoveLeft();

		void MoveRight();

		void setColorTextGameSelection(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignGameSelection(int posx);

		int getSelectedGameNumber()
		{
			return __mainGameSelected;
		}
	};
}