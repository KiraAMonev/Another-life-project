#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // ���������� ���������� SFML ��� �������
#include "Grass.h" // ���������� ������������ ���� ��� ������ Grass
#include "animal.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

const int WINDOW_WIDTH = 800; // ������ �������� ����
const int WINDOW_HEIGHT = 800; // ������ �������� ����
const int CELL_SIZE = 15; // ������ ������ ������ � �����
const int GRID_SIZE = WINDOW_WIDTH / CELL_SIZE; // ������ ����� �� ������ ������ ���� � ������� ������

const int NOT_FILL = 0;
const int IS_GRASS = 1;
const int IS_HERBIVORE = 2;
const int IS_PREDATOR = 3;

const int NUM_GRASS = 300; // ���������� �����, ������� ����� ��������� � ������
const int GRASS_LIFE_SPAN = 7; // ����������������� ����� ����� � ������
const int MAX_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;

const int MALE = 0;
const int FEMALE = 1;
const int MAX_CNT_MATING_HERBIVORES = 2;
const int MAX_CNT_MATING_PREDATOR = 6;

const int NUM_HERBIVORE = 130; //���������� ����������
const int HERBIVORES_LIFE_SPAN = 20; //����������������� ����� ����������
const int HERBIVORE_NORMAL_SATIETY = 10; //���������� ���������� �������
const int HERBIVORE_HUNGRY_SATIETY = 10; //�������, ����� ����� ���� �����
const int HERBIVORE_ADULT_AGE = 2; //"��������", �� ���� �������, ����� ����� �����-����
const int HERBIVORE_REDUCING_SATIETY = 1; //������� ����� ������� ������ �� ����

const int NUM_PREDATOR = 40; // ���������� ��������
const int PREDATOR_LIFE_SPAN = 30; //����������������� ����� � ��������
const int PREDATOR_NORMAL_SATIETY = 20; //���������� ���������� ������� � ��������
const int PREDATOR_HUNGRY_SATIETY = 14; //�������, ����� ����� ����
const int PREDATOR_ADULT_AGE = 8; //"��������", �� ���� �������, ����� ����� �����-����
const int PREDATOR_REDUCING_SATIETY = 1; //������� ����� ������� ������ �� ����

const int GRASS_RESTORING_SATIETY = 2; //������� ��������������� ��������
const int ANIMAL_RESTORING_SATIETY = 6; //������� ��������������� �������� ���������


class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // ���� SFML
    std::vector<std::vector<int>> cells; // ����� �����, �������������� ��������� ����.
    //0-����� 1-����� 2-���������� 3-������

    std::vector<std::vector<Grass>> grassCells; // ����� �����, �������������� ����� � ������������������ �����
    std::vector<std::vector<Animal>> herbivoreCells;
    std::vector<std::vector<Animal>> predatorCells;
    sf::Font font; // ����� ��� ������
    sf::Text text; // ����� ��� ����������� �������� ������

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
    std::pair<int, int> bfs(std::vector<std::vector<Animal>> herbivoreCells,int typeOfAnimal, std::vector<std::vector<int>> grid, int startX, int startY, int curSex, int& dir_x, int& dir_y);
    int randomDirection(); 

    std::pair<int, int> find_food(std::vector<std::vector<Animal>> herbivoreCells, int typeOfAnimal, std::vector<std::vector<int>> grid, int startX, int startY, int food, int& dir_x, int& dir_y);

};

#endif // !GAMEOFLIFE_H
