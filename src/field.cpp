#include "field.h"

void Field::randomizeMap(std::vector<char> symbols, std::string startMap)
{
    map = startMap;
    
    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(symbols.begin(), symbols.end(), generator);

    for (char symbol : symbols) {
        while (true) {
            int position = std::uniform_int_distribution<int>(0, map.size() - 1)(generator);

            if (map[position] == ' ') {
                map[position] = symbol;
                break;
            }
        }
    }
}

void Field::clearMap(std::vector<char> symbols, std::string& startMap)
{
    map = startMap;

    int length = map.size();
    for (char symbol : symbols) {
        int position = 0;
        while (position < length) {
            if (map[position] == symbol) {
                map[position] = ' ';
                break;
            }
            position++;
        }
    }
}

FieldGraphics::FieldGraphics()
{
    roadFigure.setFillColor(sf::Color::Black);
    roadFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
        
    wallFigure.setFillColor(sf::Color::Blue);
    wallFigure.setSize({ BLOCK_SIZE,BLOCK_SIZE });
        
    cookieFigure.setFillColor(sf::Color::Yellow);
    cookieFigure.setRadius(3.f);
}

sf::FloatRect Field::moveRectangle(const sf::FloatRect& rectangle, sf::Vector2f& offset)
{
    return { rectangle.left + offset.x, rectangle.top + offset.y, rectangle.width, rectangle.height };
}

float Field::getArea(const sf::FloatRect& rectangle)
{
    return rectangle.width * rectangle.height;
}

float Field::getBottom(const sf::FloatRect& rectangle)
{
    return rectangle.top + rectangle.height;
}

float Field::getRight(const sf::FloatRect& rectangle)
{
    return rectangle.left + rectangle.width;
}

Direction Field::selectShiftDirection(float leftShift, float rightShift, float topShift, float bottomShift, float minShift, float maxShift)
{
    Direction result = Direction::NONE;
    float bestShift = BLOCK_SIZE * WIDTH_OF_FIELD;
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

sf::Vector2f Field::getStartPosition(char marker)
{
    for (size_t y = 0; y < HEIGHT_OF_FIELD; ++y) {
        for (size_t x = 0; x < WIDTH_OF_FIELD; ++x) {
            const size_t offset = x + y * WIDTH_OF_FIELD;
            if (map[offset] == marker) {
                return { x * BLOCK_SIZE + LEFT_INDENTATION, y * BLOCK_SIZE + TOP_INDENTATION};
            }
        }
    }
    return { 0, 0 };
}

sf::Vector2f Field::getPackmanStartPosition()
{
    return getStartPosition('@');
}

sf::Vector2f Field::getGhostsStartPosition(GhostID& ghostID)
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

sf::Vector2f Field::getBonusesStartPosition(TypesBonuses& type)
{
    if (type == TypesBonuses::BOMB) {
        return getStartPosition('Q');
    }
    if (type == TypesBonuses::CYCLE) {
        return getStartPosition('W');
    }
}

bool Field::checkFieldWallsCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement, const float& speed)
{
    sf::FloatRect newBounds = moveRectangle(oldBounds, movement);
    bool changed = false;
    for (size_t i = 0; i < width * height; i++)
    {
        const Cell& cell = cells[i];
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

void Field::initializeField(int selectMap)
{
    randomizeMap(ALL_SYMBOLS, selectMap);
    width = WIDTH_OF_FIELD;
    height = HEIGHT_OF_FIELD;
    cells = new Cell[width * height];
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            const size_t offset = x + y * width;
            CellCategory category;
            
            sf::Color color;
            switch (map[offset])
            {
            case '#':
                category = CellCategory::WALL;
                break;
            case ' ':
                category = CellCategory::DOT;
                break;
            case '@':
                category = CellCategory::DOT;
                break;
            case '1':
                category = CellCategory::DOT;
                break;
            case '2':
                category = CellCategory::DOT;
                break;
            case '3':
                category = CellCategory::DOT;
                break;
            case '4':
                category = CellCategory::DOT;
                break;
            default:
                category = CellCategory::ROAD;
                break;
            }

            Cell& cell = cells[offset];
            cell.category = category;
            cell.bounds.left = x * BLOCK_SIZE + 535;
            cell.bounds.top = y * BLOCK_SIZE + 190;
            cell.bounds.width = BLOCK_SIZE;
            cell.bounds.height = BLOCK_SIZE;
        }
    }
}

void Field::drawField(sf::RenderWindow& window)
{
    FieldGraphics graphics;

    for (size_t i = 0; i < width * height; i++) {
        const Cell& cell = cells[i];
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
        if (cell.category == CellCategory::DOT) {
            graphics.roadFigure.setPosition(position);
            graphics.cookieFigure.setPosition(center.x - 1.f, center.y - 1.f);
            window.draw(graphics.roadFigure);
            window.draw(graphics.cookieFigure);
        }
    }
}

unsigned int Field::countRemainingCookies()
{
    unsigned int result = 0;

    for (size_t offset = 0; offset < width * height; offset++) {
        const Cell& cell = cells[offset];
        if (cell.category == CellCategory::DOT) {
            ++result;
        }
    }
    return result;
}

unsigned int Field::eatAllCookiesBounds(const sf::FloatRect& bounds)
{
    unsigned int cookiesCount = 0;

    for (size_t i = 0; i < width * height; i++)
    {
        Cell& cell = cells[i];
        if (cell.category != CellCategory::DOT) {
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

