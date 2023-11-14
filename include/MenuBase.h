#pragma once
#include <SFML/Graphics.hpp>

namespace game {
	class MenuBase {
	protected:
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
		sf::Color __borderColor = sf::Color::Blue;

		void setInitTextMenu(sf::Text& text, sf::String str, double xpos, double ypos);

		sf::RenderWindow& __window;

	public:
		MenuBase(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		~MenuBase()
		{
			delete[] __mainMenu;
		}

		void draw();
		void MovePrev();
		void MoveNext();

		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		void AlignMenu(int posx);

		int getSelectedMenuNumber()
		{
			return __mainMenuSelected;
		}
	};

	class Menu : public MenuBase {
	public:
		Menu(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class GameSelection : public MenuBase {
	public:
		GameSelection(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class ChoseBots : public GameSelection {
	public:
		ChoseBots(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class Maps : public GameSelection {
	public:
		Maps(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class Pause : public MenuBase {
	public:
		Pause(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class Exit : public GameSelection {
	public:
		Exit(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	class Settigns : public MenuBase
	{
	public:
		Settigns(sf::RenderWindow& window, double settignsmenux, double settignsy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};


}