#pragma once
#include <SFML/Graphics.hpp>

namespace game {

	class Menu
	{
		double __menuX;
		double __menuY;
		int __menuStep;
		int __maxMenu;
		int __sizeFont;
		int __mainMenuSelected;
		sf::Font __font;
		
		sf::Text* __mainMenu;
		sf::Color __menuTextColor = sf::Color::Blue;
		sf::Color __choseTextColor = sf::Color::Yellow;
		sf::Color __borderColor = sf::Color::Black;
		
		void setInitText(sf::Text& text, sf::String str, double xpos, double ypos);
		
		sf::RenderWindow& __window;
	public:
		
		Menu(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~Menu()
		{
			delete[] __mainMenu;
		}

		void draw();

		void MoveUp();

		void MoveDown();
		
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignMenu(int posx);

		int getSelectedMenuNumber()
		{
			return __mainMenuSelected;
		}
	};
}