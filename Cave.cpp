#include "Cave.h"
#include <random>

//  онструктор пещеры
Cave::Cave(const CaveConfig& cfg)
    : config(cfg),
    grid(cfg.height, vector<int>(cfg.width, 0)) {
}

// «аполн€ем сетку случайно
void Cave::randomInitialize() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100);

    // ƒл€ каждой клетки :
    // генерируетс€ случайное число от 0 до 100
    // если оно меньше заданного процента Ч клетка жива€
    for (int i = 0; i < config.height; ++i)
        for (int j = 0; j < config.width; ++j)
            grid[i][j] = (dist(gen) < config.chanceToStartAlive) ? 1 : 0;
}

// ѕодсчЄт живых соседей
int Cave::countAliveNeighbors(int x, int y) const {
    // смещени€ дл€ 8 соседей
    static int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    static int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int cnt = 0;

    for (int d = 0; d < 8; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        // провер€ем, что сосед не выходит за границы массива
        if (nx >= 0 && nx < config.height &&
            ny >= 0 && ny < config.width)
            cnt += grid[nx][ny];
    }
    return cnt;
}

// ќдин шаг клеточного автомата
// —оздаЄм новую сетку и делаем рачЄты по старой,
// иначе изменени€ повли€ют на соседние клетки
void Cave::doSimulationStep() {
    vector<vector<int>> newGrid = grid;

    for (int i = 0; i < config.height; ++i)
        for (int j = 0; j < config.width; ++j) {
            int neighbors = countAliveNeighbors(i, j);

            // если клетка жива€
            if (grid[i][j] == 1)
                // умирает при недостатке соседей
                newGrid[i][j] = (neighbors < config.deathLimit) ? 0 : 1;
            // если клетка не жива€
            else
                // рождаетс€ при большом количестве соседей
                newGrid[i][j] = (neighbors > config.birthLimit) ? 1 : 0;
        }
    // замен€ем старую сетку новой
    grid = newGrid;
}

// ¬озвращает сетку дл€ отрисовки
const vector<vector<int>>& Cave::getGrid() const {
    return grid;
}

int Cave::getWidth() const {
    return config.width;
}

int Cave::getHeight() const {
    return config.height;
}