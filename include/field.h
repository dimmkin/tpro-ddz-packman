#pragma once
#include <SFML/Graphics.hpp>
#include "packman.h"


enum class CellCategory {
    WALL,
    ROAD
};

class Cell {
public:
    CellCategory category;
    sf::RectangleShape bounds;
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
static const char FIELD_MAZE[] = "#####################"
                                 "#  #      ####      #"
                                 "#  #      #   # ## ##"
                                 "#  #      # # ####  #"
                                 "#  #      # #       #"
                                 "#        #  #########"
                                 "#                   #"
                                 "   @  #              "
                                 "      #              "
                                 "#     #             #"
                                 "#     #             #"
                                 "#     #             #"
                                 "#                   #"
                                 "#                   #"
                                 "#                   #"
                                 "#                   #"
                                 "#####################";

static sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset);
sf::Vector2f getPackmanStartPosition();
bool checkFieldWallsCollision(const Field& field, const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed);
void initializeField(Field& field);
void drawField(sf::RenderWindow& window, const Field& field);
