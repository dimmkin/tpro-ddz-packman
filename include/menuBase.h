/**
 * @file menuBase.h
 * @brief Содержит объявление класса MenuBase. 
 */

#pragma once
#include <SFML/Graphics.hpp>

/**
 * @namespace game
 * 
 * Это пространство имен содержит классы и функции, относящиеся к игровому модулю.
 * 
 */
namespace game {
	/**
	 * @class MenuBase
	 * 
	 * Этот класс представляет собой базовое меню для игры.
	 * 
	 */
	class MenuBase
	{
	protected:
		double __menuX;                                 // Положение меню по координате x.
		double __menuY;                                 // Положение меню по координате y. 
		int __menuStep;                                 // Размер шага меню. 
		int __maxMenu;                                  // Максимальное количество опций меню. 
		int __sizeFont;                                 // Размер шрифта опций меню. 
		int __mainMenuSelected;                         // Индекс выбранного пункта главного меню. 
                        
		sf::Font __font;                                // Шрифт, используемый для опций меню. 
                        
		sf::Text* __mainMenu;                           // Массив опций главного меню. 
		sf::Color __menuTextColor = sf::Color::Blue;    // Цвет текста для параметров меню. 
		sf::Color __choseTextColor = sf::Color::Yellow; // Цвет текста для выбранного параметра меню. 
		sf::Color __borderColor = sf::Color::Blue;      // Цвет границы меню. 

		/**
		 * @brief Установите начальные текстовые свойства для пункта меню.
		 * 
		 * @param text Текстовый объект для задания свойств.
		 * @param str  Текстовая строка для отображения.
		 * @param xpos Положение текста по координате x.
		 * @param ypos Положение текста по координате y.
		 * 
		 * @code void game::MenuBase::setInitTextMenu(sf::Text& text, sf::String str, double xpos, double ypos)
		 * {
		 *	 text.setFont(__font);
		 *	 text.setFillColor(__menuTextColor);
		 *	 text.setString(str);
		 *	 text.setCharacterSize(__sizeFont);
		 *	 text.setPosition(xpos, ypos);
		 *   text.setOutlineThickness(3);
		 *	 text.setOutlineColor(__borderColor);
		 * }
		 * @endcode 
		 */
		void setInitTextMenu(sf::Text& text, sf::String str, double xpos, double ypos);

		sf::RenderWindow& __window; // Ссылка на игровое окно.

	public:
	    /**
	     * @brief Создает объект MenuBase.
	     * 
	     * @param window   Окно отображения SFML для отображения меню.
	     * @param menux    Координата x положения меню.
	     * @param menuy    Координата позиции меню по y.
	     * @param index    Начальный индекс выбранного пункта меню.
	     * @param name     Присваивает имя массиву строк, представляющих пункты прейскуранта.
	     * @param sizeFont Размер шрифта для пунктов прейскуранта (по умолчанию = 60).
	     * @param step     Шаг по вертикали между пунктами прейскуранта (по умолчанию = 80).
		 * 
		 * @code
		 * game::MenuBase::MenuBase(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	:__window(window), __menuX(menux), __menuY(menuy), __sizeFont(sizeFont), __menuStep(step)
         *{
         *	if (!__font.loadFromFile("font/EightBits.ttf")) exit(32);
         *	__maxMenu = index;
         *	__mainMenu = new sf::Text[__maxMenu];
         *
         *	for (int i = 0, ypos = __menuY; i < __maxMenu; i++, ypos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], __menuX, ypos);
         *	__mainMenuSelected = 0;
         *
         *	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
         *}
		 * @endcode 
	     */
		MenuBase(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);

		/**
		 * @brief Уничтожает объект MenuBase и освобождает выделенную память.
		 * 
		 */
		~MenuBase()
		{
			delete[] __mainMenu;
		}

		/**
		* @brief отображает меню в окне отображения SFML.
		*/
		void draw();

		/**
		* @brief Переходит к предыдущему пункту прейскуранта.
		*/
		void MovePrev();
		
		/**
		* @brief переходит к следующему пункту прейскуранта.
		*/
		void MoveNext();

		/**
		 * @brief Задает цвет элементов, выбранного пункта прейскуранта и границы.
		 * 
		 * @param menColor  Цвет элементов.
		 * @param ChoColor  Цвет выбранного элемента 
		 * @param BordColor Цвет границы.
		 * 
		 * @code 
		 * void game::MenuBase::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
         *{
         *	__menuTextColor = menColor;
         *	__choseTextColor = ChoColor;
         *	__borderColor = BordColor;
         *
         *	for (int i = 0; i < __maxMenu; i++) {
         *		__mainMenu[i].setFillColor(__menuTextColor);
         *		__mainMenu[i].setOutlineColor(__borderColor);
         *	}
         *
         *	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
         *}
		 * @endcode
		 */
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
			sf::Color BordColor);

		/**
		* @brief Выравнивает пункты прейскуранта по горизонтали по заданной координате x.
		*
		* @param posx Координата x для выравнивания пунктов прейскуранта.
		*
		* @code 
		* void game::MenuBase::AlignMenu(int posx)
        *{
        *	double nullx = 0;
        *	for (int i = 0; i < __maxMenu; i++) {
        *		switch (posx)
        *		{
        *		case 0:
        *			nullx = 0;
        *			break;
        *		case 1:
        *			nullx = __mainMenu[i].getLocalBounds().width;
        *			break;
        *		case 2:
        *			nullx = nullx = __mainMenu[i].getLocalBounds().width / 2;
        *			break;
        *		}
        *		__mainMenu[i].setPosition(__mainMenu[i].getPosition().x - nullx, __mainMenu[i].getPosition().y);
        *	}
        *
        *}
		* @endcode
		*/
		void AlignMenu(int posx);

		/**
		* @brief Возвращает номер текущего выбранного пункта прейскуранта.
		*
		* @return номер выбранного в данный момент пункта прейскуранта.
		*
		* @code 
		* int getSelectedMenuNumber()
		*{
		*	return __mainMenuSelected;
		*}
		* @endcode
		*/
		int getSelectedMenuNumber()
		{
			return __mainMenuSelected;
		}
	};

	/**
	* @class Menu
	*
	* @brief Представляет главное меню игры.
	*/
	class Menu : public MenuBase {
	public:
		/**
		* @brief Создает объект меню.
		* @param window   Объект SFML RenderWindow.
		* @param menux    Координата x меню.
		* @param menuy    Координата y меню.
		* @param index    Индекс меню.
		* @param name     Массив названий меню.
		* @param sizeFont Размер шрифта для меню.
		* @param step     Размер шага между пунктами меню.
		*
		* @code
		* game::Menu::Menu(sf::RenderWindow& window, double menux, double menuy,
        *	int index, sf::String name[], int sizeFont, int step)
        *	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
        * {}
 		* @endcode
		*/
		Menu(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	/**
	 * @class GameSelection (выбор класса)
	 * 
	 * @brief Представляет меню выбора игры.
	 */
	class GameSelection : public MenuBase {
	public:
		/**
		 * @brief  Создает объект выбора игры.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code 
		 * game::GameSelection::GameSelection(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
         *{
         *	__maxMenu = index;
         *	__mainMenu = new sf::Text[__maxMenu];
         *
         *	for (int i = 0, xpos = __menuX; i < __maxMenu; i++, xpos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], xpos, __menuY);
         *	__mainMenuSelected = 0;
         *
         *	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
         *}
		 * @endcode
		 */
		GameSelection(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	/**
	 * @class ChoseBots Выбранных ботов.
	 * 
	 * @brief Представляет меню для выбора ботов в меню выбора игры.
	 */
	class ChoseBots : public GameSelection {
	public:
		/**
		 * @brief Создает объект ChoseBots.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code 
		 * game::ChoseBots::ChoseBots(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: GameSelection(window, menux, menuy, index, name, sizeFont, step)
         *{}
		 * @endcode
		 * 
		 */
		ChoseBots(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};
	/**
	 * @class Maps
	 * 
	 * @brief Представляет меню для выбора карт в меню выбора игры.
	 */
	class Maps : public GameSelection {
	public:
		/**
		 * @brief Создает объект Maps.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code 
		 * game::Maps::Maps(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: GameSelection(window, menux, menuy, index, name, sizeFont, step)
         *{}
		 * @endcode
		 */
		Maps(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};
	/**
	 * @class Pause
	 * 
	 * @brief Представляет меню паузы в игре.
	 */
	class Pause : public MenuBase {
	public:
		/**
		 * @brief Создает объект паузы.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.	
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code 
		 * game::Pause::Pause(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: MenuBase(window, menux, menuy, index, name, sizeFont, step)
         *{}
		 * @endcode
		 */
		Pause(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};
	/**
	 * @class Exit
	 * 
	 * @brief Представляет пункт меню для выхода из игры.
	 */
	class Exit : public GameSelection {
	public:
		/**
		 * @brief Создает опцию меню выхода.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.	
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code
		 * game::Exit::Exit(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: GameSelection(window, menux, menuy, index, name, sizeFont, step)
         *{}
		 * @endcode 
		 */
		Exit(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};

	/**
	 * @class Settings
	 * 
	 * @brief Представляет меню настроек.
	 * 
	 */
	class Settings : public MenuBase
	{
	public:
		/**
		 * @brief Создает меню настроек.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.	
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code 
		 * game::Settings::Settings(sf::RenderWindow& window, double settingsmenux, double settingsy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: MenuBase(window, settingsmenux, settingsy, index, name, sizeFont, step)
         *{
         *	__maxMenu = index;
         *	__mainMenu = new sf::Text[__maxMenu];
         *
         *	for (int i = 0, xpos = __menuX; i < __maxMenu; i++, xpos += __menuStep) setInitTextMenu(__mainMenu[i], name[i], xpos, __menuY);
         *	__mainMenuSelected = 0;
         *
         *	__mainMenu[__mainMenuSelected].setFillColor(__choseTextColor);
         *}
		 * @endcode
		 * 
		 */
		Settings(sf::RenderWindow& window, double settingsmenux, double settingsy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};
	
	/**
	 * @class EndGame
	 * 
	 * @brief Представляет собой пункт меню для завершения игры.
	 */
	class EndGame : public GameSelection {
	public:
		/**
		 * @brief Создает пункт меню эндшпиля.
		 * 
		 * @param window   Объект SFML RenderWindow.
		 * @param menux    Координата x меню.
		 * @param menuy    Координата y меню.
		 * @param index    Индекс меню.
		 * @param name     Массив названий меню.	
		 * @param sizeFont Размер шрифта для меню.
		 * @param step     Размер шага между пунктами меню.
		 * 
		 * @code
		 * game::EndGame::EndGame(sf::RenderWindow& window, double menux, double menuy,
         *	int index, sf::String name[], int sizeFont, int step)
         *	: GameSelection(window, menux, menuy, index, name, sizeFont, step)
         *{}
		 * @endcode
		 */
		EndGame(sf::RenderWindow& window, double menux, double menuy,
			int index, sf::String name[], int sizeFont = 60, int step = 80);
	};
}