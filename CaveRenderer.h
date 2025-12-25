#pragma once
#include <SFML/Graphics.hpp>
#include "Cave.h"

// Класс, отвечающий за визуализацию
class CaveRenderer {
private:
    int cellSize; // размер одной клетки в пикселях

public:
    //explicit используется для предотвращения неявных преобразований типов
    explicit CaveRenderer(int cellSize);

    // Отрисовка текущего состояния пещеры
    void draw(sf::RenderWindow& window, const Cave& cave);
};
