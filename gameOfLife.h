#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // Подключаем библиотеку SFML для графики
#include "Grass.h" // Подключаем заголовочный файл для класса Grass
#include "animal.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

const int WINDOW_WIDTH = 800; // Ширина игрового окна
const int WINDOW_HEIGHT = 800; // Высота игрового окна
const int CELL_SIZE = 14; // Размер каждой ячейки в сетке
const int GRID_SIZE = WINDOW_WIDTH / CELL_SIZE; // Размер сетки на основе ширины окна и размера ячейки

const int NOT_FILL = 0;
const int IS_GRASS = 1;
const int IS_HERBIVORE = 2;
const int IS_PREDATOR = 3;

const int NUM_GRASS = 300; // Количество травы, которая будет размещена в начале
const int GRASS_LIFE_SPAN = 5; // Продолжительность жизни травы в циклах
const int MAX_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;

const int MALE = 0;
const int FEMALE = 1;
const int MAX_CNT_MATING = 3;

const int NUM_HERBIVORE = 300; //количество травоядных
const int HERBIVORES_LIFE_SPAN = 20; //продолжительность жизни травоядных
const int HERBIVORE_NORMAL_SATIETY = 10; //нормальное количество сытости
const int HERBIVORE_HUNGRY_SATIETY = 8; //сытость, когда нужно есть траву
const int HERBIVORE_ADULT_AGE = 8; //"зрелость", то есть возраст, когда можно шпили-вили
const int HERBIVORE_REDUCING_SATIETY = 1; //сколько очков сытости падает за день

const int NUM_PREDATOR = 200; // Количество хищников
const int PREDATOR_LIFE_SPAN = 30; //продолжительность жизни у хищников
const int PREDATOR_NORMAL_SATIETY = 15; //нормальное количество сытости у хищников
const int PREDATOR_HUNGRY_SATIETY = 8; //сытость, когда нужно есть
const int PREDATOR_ADULT_AGE = 8; //"зрелость", то есть возраст, когда можно шпили-вили
const int PREDATOR_REDUCING_SATIETY = 2; //сколько очков сытости падает за день

const int GRASS_RESTORING_SATIETY = 1; //сколько восстанавливает травинка
const int ANIMAL_RESTORING_SATIETY = 6; //сколько восстанавливает поедание животного


class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // Окно SFML
    std::vector<std::vector<int>> cells; // Сетка ячеек, представляющая состояние игры.
    //0-пусто 1-трава 2-травоядное 3-хищник

    std::vector<std::vector<Grass>> grassCells; // Сетка ячеек, представляющая траву с продолжительностью жизни
    std::vector<std::vector<Animal>> herbivoreCells;
    std::vector<std::vector<Animal>> predatorCells;
    sf::Font font; // Шрифт для текста
    sf::Text text; // Текст для отображения счетчика циклов

    void placeGrass();

    void createHerbivore(int x, int y);
    void placeHerbivore();
    void reproductionHerbivore(int x, int y);
    void eatingHerbivore(int x, int y);

    void createPredator(int x, int y);
    void placePredator();
    void reproductionPredator(int x, int y);
    void eatingPredator(int x, int y);

    void placeAnimals();
    bool isWithinGrid(int x, int y);

    void update();
    void processEvents();
    void render();
    void placeText(sf::Font& font, sf::Text& text);
    void updateText(int cycleCount);
    std::pair<int, int> bfs(std::vector<std::vector<Animal>> herbivoreCells, std::vector<std::vector<int>> grid, int startX, int startY, int curSex, int& dir_x, int& dir_y);
    int randomDirection(); 
};

#endif // !GAMEOFLIFE_H
