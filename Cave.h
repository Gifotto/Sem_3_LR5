#pragma once
#include <vector>
using namespace std;

class CaveConfig {
public:
    int width, height;
    int birthLimit, deathLimit;
    int chanceToStartAlive;

    CaveConfig(int w, int h, int birth, int death, int chance)
        : width(w), height(h), birthLimit(birth),
        deathLimit(death), chanceToStartAlive(chance) {
    }
};

class Cave {
private:
    CaveConfig config;
    vector<vector<int>> grid;// двумерная сетка:
                             // 1 — стена, 0 — пустота (живая/мёртвая)
    // Подсчёт количества живых соседей клетки
    int countAliveNeighbors(int x, int y) const;
public:
    explicit Cave(const CaveConfig& cfg); // Создание пещеры с заданной конфигурацией

    void randomInitialize(); // Случайная инициализация пещеры
    void doSimulationStep(); // Выполнение одного шага клеточного автомат

    // Доступ к сетке, считывание
    const vector<vector<int>>& getGrid() const;

    // Геттеры размеров
    int getWidth() const;
    int getHeight() const;
};

//какие принципы ООП, какой паттерны, плюсы минусы
