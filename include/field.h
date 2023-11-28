#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>
#include <cassert>
#include "packman.h"

class FieldGraphics
{
public:
    sf::RectangleShape roadFigure;
    sf::RectangleShape wallFigure;
    sf::CircleShape cookieFigure;
};

enum class GhostID {
    FIRST,
    SECOND,
    THIRD,
    FORTH
};


enum class CellCategory {
    WALL,
    ROAD,
    COOKIE
};

class Cell {
public:
    CellCategory category;
    sf::FloatRect bounds;
};

class Field
{
public:
    size_t width = 0;
    size_t height = 0;
    Cell* cells = nullptr;
};

static const float BLOCK_SIZE = 40.f;
static const size_t FIELD_WIDTH = 21;
static const size_t FIELD_HEIGHT = 17;
static const char FIELD_MAZE[] = "######  #############"
                                 "#1                 2#"
                                 "# #### ####### #### #"
                                 "#                   #"
                                 "# ##  @ #   #    ## #"
                                 "#       #   #       #"
                                 "####    #####    ####"
                                 "                     "
                                 "#### # ####### # ####"
                                 "#    #         #    #"
                                 "# ## # ####### # ## #"
                                 "#            4      #"
                                 "#    #   ###   #    #"
                                 "#       3           #"
                                 "# #### ####### #### #"
                                 "#                   #"
                                 "######  #############";

void initializeFieldGraphics(FieldGraphics& graphics);
static sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset);
sf::Vector2f getPackmanStartPosition();
static sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset);
static float getArea(const sf::FloatRect& rectangle);
static float getBottom(const sf::FloatRect& rectangle);
static float getRight(const sf::FloatRect& rectangle);
static Direction selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift);
static sf::Vector2f getStartPosition(char marker);
sf::Vector2f getPackmanStartPosition();
sf::Vector2f getGhostsStartPosition(GhostID& ghostID);
bool checkFieldWallsCollision(const Field& field, const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed);
void initializeField(Field& field);
void drawField(sf::RenderWindow& window, const Field& field);

unsigned int countRemainingCookies(const Field& field);
unsigned int eatAllCookiesBounds(Field& field, const sf::FloatRect& bounds);
