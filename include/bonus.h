/**
 * @file bonus.h
 * 
 * @brief Содержит объявление класса Bonus.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

/**
 * @brief Игровое поле.
 */
class Field;

/// @brief Площадь для отрезания от шаблона бонуса бомба.
static const sf::IntRect FRAME_BOMB(0, 0, 32, 32);

/// @brief Площадь для отрезания от шаблона бонуса молния(ускорение).
static const sf::IntRect FRAME_CYCLE(32, 0, 32, 32);

/// @brief Путь к шаблону бонусов
const char BONUSES_TEXTURE[] = "image/bonus.png";

/**
 * @brief Набор типов бонусов.
 * 
 * Типы бонусов: бомба, молния.
 * 
 * @code 
 * enum class TypesBonuses {
	BOMB,
	CYCLE
	};
 * @endcode
 * 
 */
enum class TypesBonuses {
	BOMB,
	CYCLE
};

/**
 * @class Bonus
 * @brief Класс, представляющий бонусы в игре.
 * 
 * Бонусы в игре представлены в виде прямоугольника с текстурой.
 */
class Bonus
{
public:
    /// @brief Фигура
	sf::RectangleShape __figure;

	/// @brief Текстура
	sf::Texture __texture;        
	
	/// @brief Тип бонуса
	TypesBonuses __bonusType;    
	
	/// @brief Статус бонуса(активен или нет)
	bool __active;
	
	/// @brief Кол-во съеденных точек
	unsigned int __eatenDots;
	
	/// @brief Кол=во оставшихся точек
	unsigned int __remainingDots;

	/**
	 * @brief Инициализирует бонус.
	 * 
	 * Настройки бонуса включают переданные параметры и устанавливают размер бонуса в 40x40 пикселей.
	 * 
	 * @param position Позиция бонуса на карте
	 * @param texturePath Путь к шаблону бонусов
	 * @param frame Площадь от шаблона, которую надо отрезать
	 * @param type Тип бонуса
	 * @param active Бонус активирован или нет 
	 * 
	 * @return true(инитиализация прошла успешно)/false(ошибка загрузки текстуры)
	 * 
	 * @code
	 * bool Bonus::initializeBonus(const sf::Vector2f& position, const std::string& texturePath, const sf::IntRect frame, TypesBonuses type, bool active)
	 *	{
	 *		if (!__texture.loadFromFile(texturePath))
	 *			return false;
     *
	 *		__bonusType = type;
	 *		__figure.setSize({ 40.f, 40.f });
	 *		__figure.setPosition(position);
	 *		__figure.setTexture(&__texture);
	 *		__figure.setTextureRect(frame);
	 *		__active = false;
     *
	 *		return true;
	 *	}
	 * @endcode
	 */
	bool initializeBonus(const sf::Vector2f& position, const std::string& texturePath, const sf::IntRect frame, TypesBonuses type, bool active);
	
	/**
	 * @brief Отрисовка бонуса
	 * 
	 * @param window Окно в котором будет рисоваться бонус
	 * 
	 * @code void Bonus::drawBonus(sf::RenderWindow& window)
	 *{
	 *	window.draw(__figure);
	 *}
	 * @endcode
	 */
	void drawBonus(sf::RenderWindow& window);
};