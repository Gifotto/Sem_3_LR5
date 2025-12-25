#include "CaveRenderer.h"

using namespace sf;

CaveRenderer::CaveRenderer(int size)
    : cellSize(size) {
}

// чёрная клетка стена - живая клетка
// белая клетка пустота - мёртвая клетка

void CaveRenderer::draw(sf::RenderWindow& window, const Cave& cave) {
    const auto& grid = cave.getGrid();

    for (int i = 0; i < cave.getHeight(); ++i) {
        for (int j = 0; j < cave.getWidth(); ++j) {

            RectangleShape cell(Vector2f(cellSize - 1, cellSize - 1));

            cell.setPosition(j * cellSize, i * cellSize);

            // выбор цвета клетки
            cell.setFillColor(grid[i][j] ? Color::Black : Color::White);

            window.draw(cell);
        }
    }
}
