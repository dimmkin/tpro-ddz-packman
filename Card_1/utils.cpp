#include "utils.h"
#include <iostream>

// Загрузка текстуры из файла
sf::Texture loadTexture(const std::string& filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
    {
        // Обработка ошибки загрузки текстуры
        std::cout << "Failed to load texture from file: " << filename << std::endl;
    }
    return texture;
}