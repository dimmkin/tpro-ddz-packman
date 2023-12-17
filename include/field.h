/**
 * @file field.h
 * 
 * @brief Содержит объявление класса FieldGraphics, GhostID, CellCategory, Cell и Field .
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>
#include <cassert>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "../include/bonus.h"
#include "../include/packman.h"

// constants
static const float BLOCK_SIZE = 40.f;
static const size_t WIDTH_OF_FIELD = 21;
static const size_t HEIGHT_OF_FIELD = 17;
const int LEFT_INDENTATION = 535;
const int TOP_INDENTATION = 190;
const int OFFSET = 10;
const std::vector<char> ALL_SYMBOLS = { '1','2','3','4','@', 'Q', 'W', 'E' };

// Массив с картами для игры.
static char* FIELD[] = {
    "#####################"
    "#                   #"
    "# ##### ## ## ##### #"
    "#    ## ## ## ##    #"
    "# ## ## ## ## ## ## #"
    "# ##             ## #"
    "  #### ### ### ####  "
    "###### #     # ######"
    "  ##   #######   ##  "
    "# ## #         # ## #"
    "# ## # ####### # ## #"
    "#    #         #    #"
    "# ## ## ## ## ## ## #"
    "#        # #        #"
    "# ###### # # ###### #"
    "#                   #"
    "#####################",

    "#####################"
    "#                   #"
    "# ##### # # # ##### #"
    "# #     # # #     # #"
    "# # ##### # ##### # #"
    "# #               # #"
    "# #### ### ### #### #"
    "#      #     #      #"
    "###### ####### ######"
    "                     "
    "### ############# ###"
    "#                   #"
    "# ##### ##### ##### #"
    "#     #       #     #"
    "# ### # ##### # ### #"
    "#                   #"
    "#####################",

    "#####################"
    "#                   #"
    "# ##### # # # ##### #"
    "# #     # # #     # #"
    "# # ##### # ##### # #"
    "# # #           # # #"
    "# # #  ### ###  # # #"
    "#   #           #   #"
    "# #   #########   # #"
    "# # #           # # #"
    "# # # ######### # # #"
    "                     "
    "######### # #########"
    "#         #         #"
    "# ####### # ####### #"
    "#                   #"
    "#####################"
};

/**
 * @class FieldGraphics
 * 
 * @brief Представляет графическое представление карты.
 * 
 */
class FieldGraphics
{
public:

    /// @brief  Дорога, по которой движется герой 
    sf::RectangleShape __roadFigure;

    /// @brief  Стены карты
    sf::RectangleShape __wallFigure;

    /// @brief  Поедаемые фигуры
    sf::CircleShape __cookieFigure;

	/**
	 * @brief Инициализирует игровую карту.
	 * 
	 * @code
     * FieldGraphics::FieldGraphics()
     *{
     *  __roadFigure.setFillColor(sf::Color::Black);
     *  __roadFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
     *        
     *  __wallFigure.setFillColor(sf::Color::Blue);
     *  __wallFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
     *        
     *  __cookieFigure.setFillColor(sf::Color::Yellow);
     *  __cookieFigure.setRadius(3.f);
     *}
	 * @endcode
	 */
    FieldGraphics();
};

/**
 * @class GhostID
 * 
 * @brief Представляет идентификатор приведений.
 * 
 */
enum class GhostID
{
    FIRST,  // ID первого    приведения
    SECOND, // ID второго    приведения
    THIRD,  // ID третьего   приведения
    FORTH   // ID четвертого приведения
};

/**
 * @class CellCategory
 * 
 * @brief Представляет характерный элемент ировой карты.
 * 
 */
enum class CellCategory
{
    WALL,   // Стена
    ROAD,   // Дорога
    DOT     // Точка
};


/**
 * @class Cell
 * 
 * @brief Представляет клетку игровой карты.
 * 
 */
class Cell
{
public:
    CellCategory __category;    // Элемент карты
    sf::FloatRect __bounds;     // Граница карты
};

/**
 * @class Field
 * 
 * @brief Представляет поле игровой карты.
 * 
 */
class Field
{
public:

    // fields
    size_t __width = 0;         // Ширина       карты
    size_t __height = 0;        // Высота       карты
    Cell* __cells = nullptr;    // Клетка       игровой карты
    std::string __map;          // Игровая      карта
    bool __changed = false;     // Изменение    позиции бонуса(по умалчанию false)
    char* __field = FIELD[0];   // Поле игровой карты(по умолчанию первая карта массива)

    // methods

    /**
	 * @brief Устанавливает необходимую игровую карту.
	 * 
	 * @code
     * void Field::setMap()
     *{
     *  std::ifstream file("text.json");
     *  json startMap = json::parse(file);
     *  file.close();
     *  int index = startMap["Start_game"][2];
     *  __field = FIELD[index];
     *}
	 * @endcode
	 */
    void setMap();

    /**
	 * @brief Определяет случайным образом обЪекты на карте.
     * 
     * @param symbols  Массив символов для расстановки.
     * @param startMap Начальная карта(по умолчанию пустая строка).
	 * 
	 * @code
     * void Field::randomizeMap(std::vector<char> symbols, std::string startMap)
     *{
     *    if(startMap == "") {
     *        setMap();
     *        __map = __field;
     *    }
     *    else {
     *        __map = startMap;
     *    }
     *    
     *    std::random_device rd;
     *    std::mt19937 generator(rd());
     *
     *    std::shuffle(symbols.begin(), symbols.end(), generator);
     *
     *    for (char symbol : symbols) {
     *        while (true) {
     *            int position = std::uniform_int_distribution<int>(0, __map.size() - 1)(generator);
     *
     *            if (__map[position] == ' ') {
     *                __map[position] = symbol;
     *                 break;
     *            }
     *        }
     *    }
     *}
	 * @endcode
	 */
    void randomizeMap(std::vector<char> symbols, std::string startMap = "");

    /**
	 * @brief Очищает карту.
     * 
     * @param symbols  Набор символов для очистки.
     * @param startMap Начальная карта.
	 * 
	 * @code
     * void Field::clearMap(std::vector<char> symbols, std::string& startMap)
     *{
     *    __map = startMap;
     *
     *    int length = __map.size();
     *    for (char symbol : symbols) {
     *        int position = 0;
     *        while (position < length) {
     *            if (__map[position] == symbol) {
     *                __map[position] = ' ';
     *                break;
     *            }
     *            position++;
     *        }
     *    }
     *}
	 * @endcode
	 */
    void clearMap(std::vector<char> symbols, std::string& startMap);

    /**
	 * @brief Перемещает прямоугольник на определенное смещение.
     * 
     * @param rectangle Обрабатываемый прямоугольник.
     * @param offset    Смещение.
	 * 
	 * @code
     * sf::FloatRect Field::moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset)
     *{
     *    return { rectangle.left + offset.x, rectangle.top + offset.y, rectangle.width, rectangle.height };
     *}
	 * @endcode
	 */
    sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset);

    /**
	 * @brief Выдает площадь прямоугольника.
     * 
     * @param rectangle Обрабатываемый прямоугольник.
	 * 
	 * @code
     * float Field::getArea(const sf::FloatRect& rectangle)
     *{
     *    return rectangle.width * rectangle.height;
     *}
	 * @endcode
	 */
    float getArea(const sf::FloatRect& rectangle);

    /**
	 * @brief Выдает размер низа прямоугольника.
     * 
     * @param rectangle Обрабатываемый прямоугольник.
	 * 
	 * @code
     * float Field::getBottom(const sf::FloatRect& rectangle)
     *{
     *    return rectangle.top + rectangle.height;
     *}
	 * @endcode
	 */
    float getBottom(const sf::FloatRect& rectangle);

    
    /**
	 * @brief Выдает размер правой стороны прямоугольника.
     * 
     * @param rectangle Обрабатываемый прямоугольник.
	 * 
	 * @code
     * float Field::getRight(const sf::FloatRect& rectangle)
     *{
     *    return rectangle.left + rectangle.width;
     *}
	 * @endcode
	 */
    float getRight(const sf::FloatRect& rectangle);

    /**
	 * @brief Выбирает направление смещения.
     * 
     * @param leftShift   Расстояние до левой границы.
	 * @param rightShift  Расстояние до правой границы.
     * @param topShift    Расстояние до верхней границы.
     * @param bottomShift Расстояние до нижней границы.
     * @param minShift    Минимальное расстояние до границы.
     * @param maxShift    Максимальное расстояние до левой границы.
     *  
     * @return  Направление смещения
     * 
	 * @code
     * Direction Field::selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift)
     *{
     *    Direction result = Direction::NONE;
     *    float bestShift = BLOCK_SIZE * WIDTH_OF_FIELD;
     *    if ((minShift < leftShift && leftShift < maxShift) && leftShift < bestShift) {
     *        result = Direction::LEFT;
     *        bestShift = leftShift;
     *    }
     *    if ((minShift < rightShift && rightShift < maxShift) && rightShift < bestShift) {
     *        result = Direction::RIGHT;
     *        bestShift = rightShift;
     *    }
     *    if ((minShift < topShift && topShift < maxShift) && topShift < bestShift) {
     *        result = Direction::UP;
     *        bestShift = topShift;
     *    }
     *    if ((minShift < bottomShift && bottomShift < maxShift) && bottomShift < bestShift) {
     *        result = Direction::DOWN;
     *        bestShift = bottomShift;
     *    }
     *
     *    return result;
     *}
	 * @endcode
	 */
    Direction selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift);

        
    /**
	 * @brief Задает начальную позицию символа.
     * 
     * @param marker Символ по которому будет определяться позиция.
     * 
     * @return Позиция символа.
	 * 
	 * @code
     * sf::Vector2f Field::getStartPosition(char marker)
     *{
     *    for (size_t y = 0; y < HEIGHT_OF_FIELD; ++y) {
     *        for (size_t x = 0; x < WIDTH_OF_FIELD; ++x) {
     *            const size_t offset = x + y * WIDTH_OF_FIELD;
     *            if (__map[offset] == marker) {
     *                if (marker == '@') {
     *                    return { x * BLOCK_SIZE + LEFT_INDENTATION + OFFSET, y * BLOCK_SIZE + TOP_INDENTATION + OFFSET};
     *                }
     *                return { x * BLOCK_SIZE + LEFT_INDENTATION, y * BLOCK_SIZE + TOP_INDENTATION};
     *            }
     *        }
     *    }
     *    return { 0, 0 };
     *}
	 * @endcode
	 */
    sf::Vector2f getStartPosition(char marker);

            
    /**
	 * @brief Задает начальную позицию пакмана.
     *  
     * @return Позиция пакмана.
	 * 
	 * @code
     * sf::Vector2f Field::getPackmanStartPosition()
     *{
     *  return getStartPosition('@');
     *}
	 * @endcode
	 */
    sf::Vector2f getPackmanStartPosition();

    /**
	 * @brief Задает начальную позицию приведения.
     *  
     * @return Позиция приведения.
	 * 
	 * @code
     * sf::Vector2f Field::getGhostsStartPosition(GhostID& ghostID)
     *{
     *    if (ghostID == GhostID::FIRST) {
     *        return getStartPosition('1');
     *    }
     *    if (ghostID == GhostID::SECOND) {
     *        return getStartPosition('2');
     *    }
     *    if (ghostID == GhostID::THIRD) {
     *        return getStartPosition('3');
     *    }
     *    if (ghostID == GhostID::FORTH) {
     *        return getStartPosition('4');
     *    }
     *}
	 * @endcode
	 */
    sf::Vector2f getGhostsStartPosition(GhostID& ghostID);


                
    /**
	 * @brief Задает начальную позицию бонуса.
     *  
     * @return Позиция бонуса.
	 * 
	 * @code
     * sf::Vector2f Field::getBonusesStartPosition(TypesBonuses& type)
     *{
     *    if (type == TypesBonuses::BOMB) {
     *        return getStartPosition('Q');
     *    }
     *    if (type == TypesBonuses::CYCLE) {
     *        return getStartPosition('W');
     *    }
     *}
	 * @endcode
	 */
    sf::Vector2f getBonusesStartPosition(TypesBonuses& type);


                    
    /**
	 * @brief Проверяет столкновение объекта с границей.
     * 
     * @param oldBounds Исходные границы до перемещения.
     * @param movement  Вектор движения объекта.
     * @param speed     Скорость объекта.
     *  
     * @return Столкнулся ли объект или нет.
	 * 
	 * @code
     * bool Field::checkFieldWallsCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed)
     *{
     *    sf::FloatRect newBounds = moveRectangle(oldBounds, movement);
     *    bool changed = false;
     *    for (size_t i = 0; i < __width * __height; i++)
     *    {
     *        const Cell& cell = __cells[i];
     *        if (cell.__category != CellCategory::WALL)
     *        {
     *            continue;
     *        }
     *
     *        sf::FloatRect blockBound = cell.__bounds;
     *
     *        if (newBounds.intersects(blockBound))
     *        {
     *            const float bottomShift = getBottom(blockBound) - newBounds.top;
     *            const float topShift = getBottom(newBounds) - blockBound.top;
     *            const float rightShift = getRight(blockBound) - newBounds.left;
     *            const float leftShift = getRight(newBounds) - blockBound.left;
     *            const float movementShift = std::max(std::abs(movement.x), std::abs(movement.y));
     *
     *            Direction direction = selectShiftDirection(leftShift, rightShift,
     *                topShift, bottomShift,
     *                movementShift + std::numeric_limits<float>::epsilon(), 0.5f * BLOCK_SIZE);
     *            if (direction == Direction::NONE)
     *            {
     *                direction = selectShiftDirection(leftShift, rightShift,
     *                    topShift, bottomShift,
     *                    0, 0.5f * BLOCK_SIZE);
     *            }
     *            if (direction == Direction::UP) {
     *                movement.y -= topShift;
     *            }
     *            if (direction == Direction::DOWN) {
     *                movement.y += bottomShift;
     *            }
     *            if (direction == Direction::LEFT) {
     *                movement.x -= leftShift;
     *            }
     *            if (direction == Direction::RIGHT) {
     *                movement.x += rightShift;
     *            }
     *            changed = true;
     *            newBounds = moveRectangle(oldBounds, movement);
     *        }
     *    }
     *    return changed;
     *}
	 * @endcode
	 */
    bool checkFieldWallsCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed);

                    
    /**
	 * @brief Инициализирует поля карты.
     *  
	 * @code
     * void Field::initializeField()
     *{
     *    randomizeMap(ALL_SYMBOLS);
     *    __width = WIDTH_OF_FIELD;
     *    __height = HEIGHT_OF_FIELD;
     *    __cells = new Cell[__width * __height];
     *    for (size_t y = 0; y < __height; y++)
     *    {
     *        for (size_t x = 0; x < __width; x++)
     *        {
     *            const size_t offset = x + y * __width;
     *            CellCategory category;
     *            
     *            sf::Color color;
     *            switch (__map[offset])
     *            {
     *            case '#':
     *                category = CellCategory::WALL;
     *                break;
     *            case ' ':
     *                category = CellCategory::DOT;
     *                break;
     *            case '@':
     *                category = CellCategory::DOT;
     *                break;
     *            case '1':
     *                category = CellCategory::DOT;
     *                break;
     *            case '2':
     *                category = CellCategory::DOT;
     *                break;
     *            case '3':
     *                category = CellCategory::DOT;
     *                break;
     *            case '4':
     *                category = CellCategory::DOT;
     *                break;
     *            default:
     *                category = CellCategory::ROAD;
     *                break;
     *            }
     *
     *            Cell& cell = __cells[offset];
     *            cell.__category = category;
     *            cell.__bounds.left = x * BLOCK_SIZE + 535;
     *            cell.__bounds.top = y * BLOCK_SIZE + 190;
     *            cell.__bounds.width = BLOCK_SIZE;
     *            cell.__bounds.height = BLOCK_SIZE;
     *        }
     *    }
     *}
	 * @endcode
	 */
    void initializeField();

                    
    /**
	 * @brief Прорисовывает поля.
     *  
     * @param window Окно вывода.
	 * 
	 * @code
     * void Field::drawField(sf::RenderWindow& window)
     *{
     *    FieldGraphics graphics;
     *
     *    for (size_t i = 0; i < __width * __height; i++) {
     *        const Cell& cell = __cells[i];
     *        const sf::Vector2f position = { cell.__bounds.left, cell.__bounds.top };
     *        const sf::Vector2f center = position + sf::Vector2f(0.5f * cell.__bounds.width, 0.5f * cell.__bounds.height);
     *
     *        if (cell.__category == CellCategory::WALL) {
     *            graphics.__wallFigure.setPosition(position);
     *            window.draw(graphics.__wallFigure);
     *        }
     *        if (cell.__category == CellCategory::ROAD) {
     *            graphics.__roadFigure.setPosition(position);
     *            window.draw(graphics.__roadFigure);
     *        }
     *        if (cell.__category == CellCategory::DOT) {
     *            graphics.__roadFigure.setPosition(position);
     *            graphics.__cookieFigure.setPosition(center.x - 1.f, center.y - 1.f);
     *            window.draw(graphics.__roadFigure);
     *            window.draw(graphics.__cookieFigure);
     *        }
     *    }
     *}
	 * @endcode
	 */
    void drawField(sf::RenderWindow& window);


                        
    /**
	 * @brief Считает оставшиеся печеньки-очки.
     * 
     * @return Количество оставшихся очков.
	 * 
	 * @code
     * unsigned int Field::countRemainingCookies()
     *{
     *    unsigned int result = 0;
     *
     *    for (size_t offset = 0; offset < __width * __height; offset++) {
     *        const Cell& cell = __cells[offset];
     *        if (cell.__category == CellCategory::DOT) {
     *            ++result;
     *        }
     *    }
     *    return result;
     *}
	 * @endcode
	 */
    unsigned int countRemainingCookies();

                            
    /**
	 * @brief Обнаруживает и удаляет съеденые печеньки-очки.
	 * 
     * @param bounds Обрабатываемый прямоугольник. 
     *
     * @return Количество удаленных "очков-печенек"
     * 
	 * @code
     * unsigned int Field::eatAllCookiesBounds(const sf::FloatRect& bounds)
     *{
     *    unsigned int cookiesCount = 0;
     *
     *    for (size_t i = 0; i < __width * __height; i++)
     *    {
     *        Cell& cell = __cells[i];
     *        if (cell.__category != CellCategory::DOT) {
     *            continue;
     *        }
     *
     *        sf::FloatRect intersect;
     *
     *        if (cell.__bounds.intersects(bounds, intersect) && (getArea(intersect) >= 800.f)) {
     *            ++cookiesCount;
     *            cell.__category = CellCategory::ROAD;
     *        }
     *    }
     *    return cookiesCount;
     *}
	 * @endcode
	 */
    unsigned int eatAllCookiesBounds(const sf::FloatRect& bounds);
};