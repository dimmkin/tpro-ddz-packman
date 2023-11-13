#include "utils.h"
#include <iostream>


struct Field
{
    size_t width = 0;
    size_t height = 0;
    sf::RectangleShape *rects = nullptr;
};

static const sf::Color BLACK_COLOR = sf::Color(0, 0, 0);

static const float BLOCK_SIZE = 25.f;
static const size_t FIELD_WIDTH = 31;
static const size_t FIELD_HEIGHT = 33;
static const char FIELD_MAZE[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,
    1,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,
    1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,
    1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,
    1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,
    1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,
    1,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,
    1,0,1,1,0,0,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1,0,1,
    1,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,
    1,0,1,1,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,
    1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,
    1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,
    1,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1,
    1,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,
    1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,
    1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,1,
    1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,1,0,0,0,0,0,0,1,0,0,1,
    1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};


// Превращаем наш массив в поле
void initializeField(Field& field, const sf::Texture& texture)
{
    field.width = FIELD_WIDTH;
    field.height = FIELD_HEIGHT;
    field.rects = new sf::RectangleShape[field.width * field.height];
    for (size_t y = 0; y < field.height; y++)
    {
        for (size_t x = 0; x < field.width; x++)
        {
            const size_t offset = x + y * field.width;
            sf::RectangleShape &rect = field.rects[offset];
            rect.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
            rect.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

            if (FIELD_MAZE[offset] == 1)
            {
                rect.setTexture(&texture);
            }
            else
            {
                rect.setFillColor(BLACK_COLOR);
            }
            
        }
    }
}


// Прорисовываем каждый элемент поля
void drawField(sf::RenderWindow &window, const Field &field)
{
    for (size_t i = 0; i < field.width * field.height; i++)
    {
        window.draw(field.rects[i]);
    }
}

// Воспроизводим наше поле
void render(sf::RenderWindow& window, const Field& field)
{
    window.clear();
    drawField(window, field);
    window.display();
}

int main(int, char* [])
{
    sf::RenderWindow window(sf::VideoMode(775, 825), "PacMan Game Clone");

    // Загрузка текстуры
    sf::Texture fieldTexture = loadTexture("pixelFields/pixel_3.jpg");

    // Накладываем текстуры на поле
    Field field;
    initializeField(field, fieldTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        render(window, field);
    }

    return 0;
}