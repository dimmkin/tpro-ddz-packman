#include "field.h"

static sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset)
{
    return { rectangle.left + offset.x, rectangle.top + offset.y, rectangle.width, rectangle.height };
}

sf::Vector2f getPackmanStartPosition()
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            const size_t offset = x + y * FIELD_WIDTH;
            if (FIELD_MAZE[offset] == '@')
            {
                return { x * BLOCK_SIZE + 535, y * BLOCK_SIZE + 190 };
            }
        }
    }
    return { 0, 0 };
}

bool checkFieldWallsCollision(const Field& field, const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed)
{
    sf::FloatRect newBounds = moveRectangle(oldBounds, movement);
    bool changed = false;
    for (size_t i = 0, n = field.width * field.height; i < n; i++)
    {
        const Cell& cell = field.cells[i];
        if (cell.category == CellCategory::ROAD)
        {
            continue;
        }

        sf::FloatRect blockBound = cell.bounds.getGlobalBounds();
        if (newBounds.intersects(blockBound))
        {
            if (movement.y < 0)
            {
                movement.y += blockBound.top + blockBound.height - newBounds.top;
            }
            else if (movement.y > 0)
            {
                movement.y -= newBounds.top + newBounds.height - blockBound.top;
            }
            if (movement.x < 0)
            {
                movement.x += blockBound.left + blockBound.width - newBounds.left;
            }
            else if (movement.x > 0)
            {
                movement.x -= newBounds.left + newBounds.width - blockBound.left;
            }
            changed = true;
            newBounds = moveRectangle(oldBounds, movement);
        }
    }
    return changed;
}

void initializeField(Field& field)
{
    field.width = FIELD_WIDTH;
    field.height = FIELD_HEIGHT;
    field.cells = new Cell[field.width * field.height];
    for (size_t y = 0; y < field.height; y++)
    {
        for (size_t x = 0; x < field.width; x++)
        {
            const size_t offset = x + y * field.width;
            CellCategory category;
            sf::Color color;

            if (FIELD_MAZE[offset] == '#')
            {
                category = CellCategory::WALL;
                color = sf::Color::Blue;
            }
            else
            {
                category = CellCategory::ROAD;
                color = sf::Color::Black;
            }

            Cell& cell = field.cells[offset];
            cell.category = category;
            cell.bounds.setPosition(x * BLOCK_SIZE + 535, y * BLOCK_SIZE + 190);
            cell.bounds.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            cell.bounds.setFillColor(color);
        }
    }
}

void drawField(sf::RenderWindow& window, const Field& field)
{
    for (size_t i = 0; i < field.width * field.height; i++)
    {
        window.draw(field.cells[i].bounds);
    }
}
