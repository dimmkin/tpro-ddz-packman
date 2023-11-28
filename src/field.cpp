#include "field.h"

void initializeFieldGraphics(FieldGraphics& graphics)
{
    graphics.roadFigure.setFillColor(sf::Color::Black);
    graphics.roadFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
    
    graphics.wallFigure.setFillColor(sf::Color::Blue);
    graphics.wallFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
    
    graphics.cookieFigure.setFillColor(sf::Color::Yellow);
    graphics.cookieFigure.setRadius(3.f);
}

static sf::FloatRect moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset)
{
    return { rectangle.left + offset.x, rectangle.top + offset.y, rectangle.width, rectangle.height };
}

static float getArea(const sf::FloatRect& rectangle)
{
    return rectangle.width * rectangle.height;
}

static float getBottom(const sf::FloatRect& rectangle)
{
    return rectangle.top + rectangle.height;
}

static float getRight(const sf::FloatRect& rectangle)
{
    return rectangle.left + rectangle.width;
}

static Direction selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift)
{
    Direction result = Direction::NONE;
    float bestShift = BLOCK_SIZE * FIELD_WIDTH;
    if ((minShift < leftShift && leftShift < maxShift) && leftShift < bestShift) {
        result = Direction::LEFT;
        bestShift = leftShift;
    }
    if ((minShift < rightShift && rightShift < maxShift) && rightShift < bestShift) {
        result = Direction::RIGHT;
        bestShift = rightShift;
    }
    if ((minShift < topShift && topShift < maxShift) && topShift < bestShift) {
        result = Direction::UP;
        bestShift = topShift;
    }
    if ((minShift < bottomShift && bottomShift < maxShift) && bottomShift < bestShift) {
        result = Direction::DOWN;
        bestShift = bottomShift;
    }

    return result;
}

static sf::Vector2f getStartPosition(char marker)
{
    for (size_t y = 0; y < FIELD_HEIGHT; ++y) {
        for (size_t x = 0; x < FIELD_WIDTH; ++x) {
            const size_t offset = x + y * FIELD_WIDTH;
            if (FIELD_MAZE[offset] == marker) {
                return { x * BLOCK_SIZE + 535, y * BLOCK_SIZE + 190 };
            }
        }
    }
    return { 0, 0 };
}

sf::Vector2f getPackmanStartPosition()
{
    return getStartPosition('@');
}

sf::Vector2f getGhostsStartPosition(GhostID& ghostID)
{
    if (ghostID == GhostID::FIRST) {
        return getStartPosition('1');
    }
    if (ghostID == GhostID::SECOND) {
        return getStartPosition('2');
    }
    if (ghostID == GhostID::THIRD) {
        return getStartPosition('3');
    }
    if (ghostID == GhostID::FORTH) {
        return getStartPosition('4');
    }
}

bool checkFieldWallsCollision(const Field& field, const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed)
{
    sf::FloatRect newBounds = moveRectangle(oldBounds, movement);
    bool changed = false;
    for (size_t i = 0; i < field.width * field.height; i++)
    {
        const Cell& cell = field.cells[i];
        if (cell.category != CellCategory::WALL)
        {
            continue;
        }

        sf::FloatRect blockBound = cell.bounds;
        if (newBounds.intersects(blockBound))
        {
            const float bottomShift = getBottom(blockBound) - newBounds.top;
            const float topShift = getBottom(newBounds) - blockBound.top;
            const float rightShift = getRight(blockBound) - newBounds.left;
            const float leftShift = getRight(newBounds) - blockBound.left;
            const float movementShift = std::max(std::abs(movement.x), std::abs(movement.y));

            Direction direction = selectShiftDirection(leftShift, rightShift,
                topShift, bottomShift,
                movementShift + std::numeric_limits<float>::epsilon(), 0.5f * BLOCK_SIZE);
            if (direction == Direction::NONE)
            {
                direction = selectShiftDirection(leftShift, rightShift,
                    topShift, bottomShift,
                    0, 0.5f * BLOCK_SIZE);
            }
            if (direction == Direction::UP) {
                movement.y -= topShift;
            }
            if (direction == Direction::DOWN) {
                movement.y += bottomShift;
            }
            if (direction == Direction::LEFT) {
                movement.x -= leftShift;
            }
            if (direction == Direction::RIGHT) {
                movement.x += rightShift;
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
            switch (FIELD_MAZE[offset])
            {
            case '#':
                category = CellCategory::WALL;
                break;
            case ' ':
                category = CellCategory::COOKIE;
                break;
            case '1':
                category = CellCategory::COOKIE;
                break;
            case '2':
                category = CellCategory::COOKIE;
                break;
            case '3':
                category = CellCategory::COOKIE;
                break;
            case '4':
                category = CellCategory::COOKIE;
                break;
            default:
                category = CellCategory::ROAD;
                break;
            }

            Cell& cell = field.cells[offset];
            cell.category = category;
            cell.bounds.left = x * BLOCK_SIZE + 535;
            cell.bounds.top = y * BLOCK_SIZE + 190;
            cell.bounds.width = BLOCK_SIZE;
            cell.bounds.height = BLOCK_SIZE;
        }
    }
}

void drawField(sf::RenderWindow& window, const Field& field)
{
    FieldGraphics graphics;
    initializeFieldGraphics(graphics);

    for (size_t i = 0; i < field.width * field.height; i++) {
        const Cell& cell = field.cells[i];
        const sf::Vector2f position = { cell.bounds.left, cell.bounds.top };
        const sf::Vector2f center = position + sf::Vector2f(0.5f * cell.bounds.width, 0.5f * cell.bounds.height);

        if (cell.category == CellCategory::WALL) {
            graphics.wallFigure.setPosition(position);
            window.draw(graphics.wallFigure);
        }
        if (cell.category == CellCategory::ROAD) {
            graphics.roadFigure.setPosition(position);
            window.draw(graphics.roadFigure);
        }
        if (cell.category == CellCategory::COOKIE) {
            graphics.roadFigure.setPosition(position);
            graphics.cookieFigure.setPosition(center.x - 1.f, center.y - 1.f);
            window.draw(graphics.roadFigure);
            window.draw(graphics.cookieFigure);
        }
    }
}

unsigned int countRemainingCookies(const Field& field)
{
    unsigned int result = 0;

    for (size_t offset = 0; offset < field.width * field.height; offset++) {
        const Cell& cell = field.cells[offset];
        if (cell.category == CellCategory::COOKIE) {
            ++result;
        }
    }
    return result;
}

unsigned int eatAllCookiesBounds(Field& field, const sf::FloatRect& bounds)
{
    unsigned int cookiesCount = 0;

    for (size_t i = 0; i < field.width * field.height; i++)
    {
        Cell& cell = field.cells[i];
        if (cell.category != CellCategory::COOKIE) {
            continue;
        }

        sf::FloatRect intersect;

        if (cell.bounds.intersects(bounds, intersect) && (getArea(intersect) >= 800.f)) {
            ++cookiesCount;
            cell.category = CellCategory::ROAD;
        }
    }
    return cookiesCount;
}