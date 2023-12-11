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
const std::vector<char> ALL_SYMBOLS = { '1','2','3','4','@', 'Q', 'W', 'E' };

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

class FieldGraphics
{
public:
    sf::RectangleShape __roadFigure;
    sf::RectangleShape __wallFigure;
    sf::CircleShape __cookieFigure;

    FieldGraphics();
};

enum class GhostID
{
    FIRST,
    SECOND,
    THIRD,
    FORTH
};

enum class CellCategory
{
    WALL,
    ROAD,
    DOT
};

class Cell
{
public:
    CellCategory __category;
    sf::FloatRect __bounds;
};

class Field
{
public:

    // fields
    static const std::string __randomizedMap;
    size_t __width = 0;
    size_t __height = 0;
    Cell* __cells = nullptr;
    std::string __map;
    bool __changed = false;
    char* __field = FIELD[0]; 

    // methods
    void setMap();
    void randomizeMap(std::vector<char> symbols, std::string startMap = "");
    void clearMap(std::vector<char> symbols, std::string& startMap);
    sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset);
    float getArea(const sf::FloatRect& rectangle);
    float getBottom(const sf::FloatRect& rectangle);
    float getRight(const sf::FloatRect& rectangle);
    Direction selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift);
    sf::Vector2f getStartPosition(char marker);
    sf::Vector2f getPackmanStartPosition();
    sf::Vector2f getGhostsStartPosition(GhostID& ghostID);
    sf::Vector2f getBonusesStartPosition(TypesBonuses& type);
    bool checkFieldWallsCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed);
    void initializeField();
    void drawField(sf::RenderWindow& window);
    unsigned int countRemainingCookies();
    unsigned int eatAllCookiesBounds(const sf::FloatRect& bounds);
};