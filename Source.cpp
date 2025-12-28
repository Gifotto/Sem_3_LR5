#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Cave.h"
#include "CaveRenderer.h"
#include "Commands.h"


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

    StepCommand stepCommand(cave);
    ResetCommand resetCommand(cave);
    map<sf::Keyboard::Key, Command*> commands;
    commands[sf::Keyboard::Space] = &stepCommand;
    commands[sf::Keyboard::R] = &resetCommand;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // закрытие окна
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed) {
                auto it = commands.find(event.key.code);
                if (it != commands.end()) {
                    it->second->execute();
                }
            }
        }
        

        // отрисовка
        window.clear(sf::Color::White);
        renderer.draw(window, cave);
        window.display();
    }
}

