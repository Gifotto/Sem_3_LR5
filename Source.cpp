#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cave.h"
#include "CaveRenderer.h"

using namespace std;

int main() {
    int width, height, birth, death, chance;

    cout << "Width: ";  cin >> width;
    cout << "Height: "; cin >> height;
    cout << "Birth limit: "; cin >> birth;
    cout << "Death limit: "; cin >> death;
    cout << "Chance Birth (0-100): "; cin >> chance;

    CaveConfig config(width, height, birth, death, chance);
    Cave cave(config);

    // Начальная генерация
    cave.randomInitialize();

    // Подбор размера клетки под окно
    int cellSize = max(1, min(600 / width, 600 / height));
    CaveRenderer renderer(cellSize);

    sf::RenderWindow window(
        sf::VideoMode(width * cellSize, height * cellSize), 
        "Cave Generator");

    bool step = true; // флаг выполнения шага

    // таймер
    //sf::Clock clock;
    //sf::Time stepDelay = sf::milliseconds(200); // скорость симуляции

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // закрытие окна
            if (event.type == sf::Event::Closed)
                window.close();

            
            // шаг по нажатию SPACE
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space)
                step = true;
                
        }
        /*
        // автоматический шаг симуляции
        if (clock.getElapsedTime() >= stepDelay) {
            cave.doSimulationStep();
            clock.restart();
        }
        */
        
        // выполняем шаг симуляции
        if (step) {
            cave.doSimulationStep();
            step = false;
        }
        

        // отрисовка
        window.clear(sf::Color::White);
        renderer.draw(window, cave);
        window.display();
    }
}

