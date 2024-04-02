#include "gameOfLife.h"

GameOfLife::GameOfLife() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // Создание SFML окна
    cells.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0)); // Изменение размера сетки ячеек
    srand(time(nullptr)); // Инициализация генератора случайных чисел

    placeGrass(); // Размещение начальной травы
    //placeHerbivore(); // Размещение начальных травоядных
    placeAnimals();
    placeText(font, text);
}

void GameOfLife::run() {
    sf::Clock clock; // Создание SFML часов
    sf::Time elapsed; // Прошедшее время
    int cycleCount = 0; // Счетчик циклов
    while (window.isOpen()) { // Основной игровой цикл
        elapsed += clock.restart(); // Перезапуск часов и добавление прошедшего времени
        processEvents(); // Обработка событий
        if (elapsed.asMilliseconds() >= 700) { // Если прошла одна секунда
            update(); // Обновление состояния игры
            elapsed = sf::Time::Zero; // Сброс прошедшего времени
            ++cycleCount; // Увеличение счетчика циклов
            updateText(cycleCount); // Обновление текста с количеством циклов
        }
        render(); // Отрисовка состояния игры
    }
}

bool GameOfLife::isWithinGrid(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}


void GameOfLife::placeGrass() {
    grassCells.resize(GRID_SIZE, std::vector<Grass>(GRID_SIZE)); // Изменение размера сетки травы
    for (int i = 0; i < NUM_GRASS; ++i) { // Цикл для размещения травы
        int x = rand() % GRID_SIZE; // Случайное значение x
        int y = rand() % GRID_SIZE; // Случайное значение y
        cells[x][y] = IS_GRASS; // Установка ячейки для содержания травы
        grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // Установка продолжительности жизни для травы
    }
}

void GameOfLife::createHerbivore(int x, int y) {
    herbivoreCells[x][y].setLifeSpan(HERBIVORES_LIFE_SPAN); // Установка жизни травоядного
    herbivoreCells[x][y].setSatiety(HERBIVORE_NORMAL_SATIETY); // Установка сытости травоядного
    herbivoreCells[x][y].setSex(); // Установка пола
}


//void GameOfLife::placeHerbivore() {
//    herbivoreCells.resize(GRID_SIZE, std::vector<Animal>(GRID_SIZE)); // Изменение размера сетки травоядных
//    for (int i = 0; i < NUM_HERBIVORE; ++i) { // Цикл начального размещения травоядных
//        int x = rand() % GRID_SIZE;
//        int y = rand() % GRID_SIZE;
//        if (cells[x][y] == NOT_FILL || cells[x][y] == IS_GRASS) { // Если в клетке ничего нет, то занимаем её травоядным
//            grassCells[x][y].setLifeSpan(0);
//            cells[x][y] = IS_HERBIVORE; // Ставим флаг, что она занята травоядным
//            createHerbivore(x, y);
//        }
//    }
//}


//void GameOfLife::placeAnimals() {
//    herbivoreCells.resize(GRID_SIZE, std::vector<Animal>(GRID_SIZE));
//    predatorCells.resize(GRID_SIZE, std::vector<Animal>(GRID_SIZE));
//    for (int i = 0; i < NUM_HERBIVORE+NUM_PREDATOR; ++i) { // Цикл начального размещения травоядных
//        int x = rand() % GRID_SIZE;
//        int y = rand() % GRID_SIZE;
//        if (cells[x][y] == NOT_FILL || cells[x][y] == IS_GRASS && i < NUM_HERBIVORE) { // Если в клетке ничего нет, то занимаем её травоядным
//            grassCells[x][y].setLifeSpan(0);
//            cells[x][y] = IS_HERBIVORE; // Ставим флаг, что она занята травоядным
//            createHerbivore(x, y);
//        }
//        else if (cells[x][y] == NOT_FILL || cells[x][y] == IS_GRASS && i >= NUM_HERBIVORE) {
//            grassCells[x][y].setLifeSpan(0);
//            cells[x][y] = IS_PREDATOR; // Ставим флаг, что она занята травоядным
//            createPredator(x, y);
//        }
//    }
//}

void GameOfLife::placeAnimals() {
    herbivoreCells.resize(GRID_SIZE, std::vector<Animal>(GRID_SIZE));
    predatorCells.resize(GRID_SIZE, std::vector<Animal>(GRID_SIZE));
    for (int i = 0; i < NUM_HERBIVORE + NUM_PREDATOR; ++i) { // Цикл начального размещения травоядных
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        while (cells[x][y] == IS_HERBIVORE || cells[x][y] == IS_PREDATOR)
        {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        }

        if (i < NUM_HERBIVORE)
        {
            grassCells[x][y].setLifeSpan(0);
            cells[x][y] = IS_HERBIVORE; // Ставим флаг, что она занята травоядным
            createHerbivore(x, y);
        }
        else
        {
            grassCells[x][y].setLifeSpan(0);
            cells[x][y] = IS_PREDATOR; // Ставим флаг, что она занята травоядным
            createPredator(x, y);
        }
    }
}

void GameOfLife::reproductionHerbivore(int x, int y) {
    int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
    int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
    for (int i = 0; i < 8; i++) {
        int n_x = x + dx[i];
        int n_y = y + dy[i];
        if (isWithinGrid(n_x, n_y)) {
            if (cells[n_x][n_y] == IS_HERBIVORE && herbivoreCells[n_x][n_y].getSex() != herbivoreCells[x][y].getSex() && herbivoreCells[n_x][n_y].possibilityOfReproduction()) {
                int cnt_baby = rand() % 4;
                for (int j = 0; j < cnt_baby; j++)
                {
                    int birth_x = x + (rand() % 3-1);//было (rand() % 5 - 2)
                    int birth_y = y + (rand() % 3-1);
                    if (isWithinGrid(birth_x, birth_y) && (cells[birth_x][birth_y] == NOT_FILL || cells[birth_x][birth_y] == IS_GRASS)) {
                        cells[birth_x][birth_y] = IS_HERBIVORE;
                        createHerbivore(birth_x, birth_y);
                    }
                }
            }
        }
    }
}
////////////////////// животное ест траву рядом, не вставая на нее?=======================================================================================================================
void GameOfLife::eatingHerbivore(int x, int y) { //функция, которая позволяет травоядным кушать
    if (herbivoreCells[x][y].isHungry(HERBIVORE_HUNGRY_SATIETY) == true) { // проверяет, голодно ли животное в этой клетке
        int dx[] = { 0, 0, 1, 1, 1, -1, -1, -1 };
        int dy[] = { 1, -1, 0, 1, -1, 0, 1, -1 };
        for (int i = 0; i < 8; i++) {
            int eating_x = x + dx[i];
            int eating_y = y + dy[i];
            if (eating_x > 0 && eating_x < GRID_SIZE && eating_y > 0 && eating_y < GRID_SIZE) {
                if (grassCells[eating_x][eating_y].getLifeSpan() != 0) { //проверяет, есть ли вокруг травинка. Если да-съедаем её
                    int new_satiety = herbivoreCells[x][y].getSatiety() + GRASS_RESTORING_SATIETY;
                    herbivoreCells[x][y].setSatiety(new_satiety);
                    grassCells[eating_x][eating_y].setLifeSpan(0);
                    if (cells[eating_x][eating_y] == IS_GRASS) //если в отображаемой клетке была трава, то очищаем клетку
                        cells[eating_x][eating_y] = NOT_FILL;
                    eatingHerbivore(x, y); //рекурсивно запустим функцию, которая будет выполняться пока животное голодно
                }
            }
        }
    }
}


void GameOfLife::createPredator(int x, int y) {
    predatorCells[x][y].setLifeSpan(PREDATOR_LIFE_SPAN);
    predatorCells[x][y].setSatiety(PREDATOR_NORMAL_SATIETY);
    predatorCells[x][y].setSex();
}

//void GameOfLife::reproductionPredator(int x, int y) {
//    int cnt_baby = rand() % 4;
//    int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
//    int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
//    for (int i = 0; i < 8; i++) {
//        int n_x = x + dx[i];
//        int n_y = y + dy[i];
//        if (n_x >= 0 && n_x < GRID_SIZE && n_y >= 0 && n_y < GRID_SIZE) {
//            if (cells[n_x][n_y] == IS_PREDATOR && predatorCells[n_x][n_y].getSex() != predatorCells[x][y].getSex() && predatorCells[n_x][n_y].possibilityOfReproduction()) {
//                for (int j = 0; j < cnt_baby; j++) {
//                    int birth_x = x + (rand() % 5 - 2);
//                    int birth_y = y + (rand() % 5 - 2);
//                    if (birth_x >= 0 && birth_x < GRID_SIZE && birth_y >= 0 && birth_y < GRID_SIZE && (cells[birth_x][birth_y] == NOT_FILL || cells[birth_x][birth_y] == IS_GRASS)) {
//                        cells[birth_x][birth_y] = IS_PREDATOR;
//                        createPredator(birth_x, birth_y);
//                    }
//                }
//            }
//        }
//    }
//}

void GameOfLife::reproductionPredator(int x, int y) {
    const int num_directions = 8;
    int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
    int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

    for (int i = 0; i < num_directions; i++) {
        int n_x = x + dx[i];
        int n_y = y + dy[i];

        if (isWithinGrid(n_x, n_y) && cells[n_x][n_y] == IS_PREDATOR && predatorCells[n_x][n_y].getSex() != predatorCells[x][y].getSex() && predatorCells[n_x][n_y].possibilityOfReproduction()) {
            int cnt_baby = rand() % 4;
            for (int j = 0; j < cnt_baby; j++) {
                int birth_x = x + (rand() % 3 - 1);
                int birth_y = y + (rand() % 3 - 1);

                if (isWithinGrid(birth_x, birth_y) && (cells[birth_x][birth_y] == NOT_FILL || cells[birth_x][birth_y] == IS_GRASS)) {
                    cells[birth_x][birth_y] = IS_PREDATOR;
                    createPredator(birth_x, birth_y);
                }
            }
        }
    }
}



void GameOfLife::eatingPredator(int x, int y) { //функция, которая позволяет травоядным кушать
    if (predatorCells[x][y].isHungry(PREDATOR_HUNGRY_SATIETY) == true) { // проверяет, голодно ли животное в этой клетке
        int dx[] = { 0, 0, 1, 1, 1, -1, -1, -1 };
        int dy[] = { 1, -1, 0, 1, -1, 0, 1, -1 };
        for (int i = 0; i < 8; i++) {
            int eating_x = x + dx[i];
            int eating_y = y + dy[i];
            if (eating_x > 0 && eating_x < GRID_SIZE && eating_y > 0 && eating_y < GRID_SIZE) {
                if (herbivoreCells[eating_x][eating_y].getLifeSpan() != 0) { //проверяет, есть ли вокруг травинка. Если да-съедаем её
                    int new_satiety = predatorCells[x][y].getSatiety() + ANIMAL_RESTORING_SATIETY;
                    predatorCells[x][y].setSatiety(new_satiety);
                    herbivoreCells[eating_x][eating_y].setLifeSpan(0);
                    if (cells[eating_x][eating_y] == IS_HERBIVORE) //если в отображаемой клетке была трава, то очищаем клетку
                        cells[eating_x][eating_y] = NOT_FILL;
                    eatingPredator(x, y); //рекурсивно запустим функцию, которая будет выполняться пока животное голодно
                }
            }
        }
    }
}


void GameOfLife::update() {
    for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == IS_GRASS) {
                grassCells[x][y].decreaseLifeSpan(); // Уменьшаем продолжительность жизни травы
                if (!grassCells[x][y].isAlive()) { // Если трава умерла
                    cells[x][y] = NOT_FILL; // Удаляем траву из ячейки
                    // Генерация новых трав
                    for (int i = 0; i < 10; ++i) {
                        int new_x = x + (rand() % 5 - 2);
                        int new_y = y + (rand() % 5 - 2);
                        if (new_x >= 0 && new_x < GRID_SIZE && new_y >= 0 && new_y < GRID_SIZE && cells[new_x][new_y] == NOT_FILL) {
                            cells[new_x][new_y] = IS_GRASS;
                            grassCells[new_x][new_y].setLifeSpan(GRASS_LIFE_SPAN);
                        }
                    }
                }
            }
            else if (cells[x][y] == IS_HERBIVORE) {
                herbivoreCells[x][y].decreaseLifeSpan();
                herbivoreCells[x][y].decreaseSatiety(HERBIVORE_REDUCING_SATIETY);
                if (!herbivoreCells[x][y].isAlive()) {
                    cells[x][y] = NOT_FILL;
                }
                else {
                    if (herbivoreCells[x][y].possibilityOfReproduction()) {
                        int d_x = 0;
                        int d_y = 0;
                        std:: pair<int, int> d = bfs(herbivoreCells, cells, x, y, herbivoreCells[x][y].getSex(), d_x, d_y);
                        d_x = d.first;
                        d_y = d.second;
                        if (d_x + x < GRID_SIZE && d_x + x>0 && d_y + y < GRID_SIZE && d_y + y>0 && cells[x + d_x][y + d_y] != IS_HERBIVORE) {
                            cells[x + d_x][y + d_y] = IS_HERBIVORE;
                            cells[x][y] = NOT_FILL;
                            herbivoreCells[x + d_x][y + d_y] = herbivoreCells[x][y];
                        } else if(cells[x + d_x][y + d_y] == IS_HERBIVORE) { 
                            reproductionHerbivore(x, y);
                        }
                    }
                    else {
                        int d_x = randomDirection();//Здесь мы просто выбираем случайное направление для движеняи и задаем это движение через перезаписывыание в новые клетки текущего живтного
                        int d_y = randomDirection();
                        if (d_x + x < GRID_SIZE && d_x + x>0 && d_y + y < GRID_SIZE && d_y + y>0 && cells[x + d_x][y + d_y] != IS_HERBIVORE) {
                            cells[x + d_x][y + d_y] = IS_HERBIVORE;
                            cells[x][y] = NOT_FILL;
                            herbivoreCells[x + d_x][y + d_y] = herbivoreCells[x][y];
                        }
                    }
                    eatingHerbivore(x, y);
                }
            }
            else if (cells[x][y] == IS_PREDATOR) {
                predatorCells[x][y].decreaseLifeSpan();
                predatorCells[x][y].decreaseSatiety(PREDATOR_REDUCING_SATIETY);
                if (!predatorCells[x][y].isAlive()) {
                    cells[x][y] = NOT_FILL;
                }
                else {
                    if (predatorCells[x][y].possibilityOfReproduction()) {
                        int d_x = 0;
                        int d_y = 0;
                        std::pair<int, int> d = bfs(predatorCells, cells, x, y, predatorCells[x][y].getSex(), d_x, d_y);
                        d_x = d.first;
                        d_y = d.second;
                        if (d_x + x < GRID_SIZE && d_x + x>0 && d_y + y < GRID_SIZE && d_y + y>0 && cells[x + d_x][y + d_y] != IS_PREDATOR) {
                            cells[x + d_x][y + d_y] = IS_PREDATOR;
                            cells[x][y] = NOT_FILL;
                            predatorCells[x + d_x][y + d_y] = predatorCells[x][y];
                        }
                        else if (cells[x + d_x][y + d_y] == IS_PREDATOR) {
                            reproductionPredator(x, y);
                        }
                    }
                    else {
                        int d_x = randomDirection();//Здесь мы просто выбираем случайное направление для движеняи и задаем это движение через перезаписывыание в новые клетки текущего живтного
                        int d_y = randomDirection();
                        if (d_x + x < GRID_SIZE && d_x + x>0 && d_y + y < GRID_SIZE && d_y + y>0 && cells[x + d_x][y + d_y] != IS_PREDATOR) {
                            cells[x + d_x][y + d_y] = IS_PREDATOR;
                            cells[x][y] = NOT_FILL;
                            predatorCells[x + d_x][y + d_y] = predatorCells[x][y];
                        }
                    }
                    eatingPredator(x, y);
                }
            }
        }
    }
}

void GameOfLife::processEvents() {
    sf::Event event; // Событие SFML
    while (window.pollEvent(event)) { // Проверка событий
        if (event.type == sf::Event::Closed) // Если окно закрыто
            window.close(); // Закрываем окно
    }
}

void GameOfLife::render() {
    window.clear(sf::Color(240, 255, 240)); // Очистка окна бледно-зеленым цветом
    for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == IS_GRASS || cells[x][y] == IS_HERBIVORE || cells[x][y] == IS_PREDATOR) { // Если ячейка содержит что-то
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // Создаем прямоугольник для ячейки
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE); // Позиционируем ячейку
                if (cells[x][y] == IS_GRASS)
                    cell.setFillColor(sf::Color(34, 139, 34)); // Устанавливаем цвет травы
                else if (cells[x][y] == IS_HERBIVORE)
                    cell.setFillColor(sf::Color(210, 105, 30)); // Устанавливаем цвет травоядных
                else if (cells[x][y] == IS_PREDATOR)
                    cell.setFillColor(sf::Color(178, 34, 34));
                window.draw(cell); // Рисуем ячейку с травой или травоядными
            }
        }
    }
    window.draw(text); // Рисуем текст
    window.display(); // Отображаем отрисованный кадр
}

void GameOfLife::placeText(sf::Font& font, sf::Text& text) {
    font.loadFromFile("Font/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black); // Установка цвета текста
    text.setCharacterSize(35);
    text.setPosition(50, 30);
}

void GameOfLife::updateText(int cycleCount) {
    text.setString(std::to_string(cycleCount)); // Устанавливаем текст для отображения количества циклов
    text.setPosition(50, 30);
}
int GameOfLife::randomDirection(){
    // Создание генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1, 1); // Равномерное распределение чисел в диапазоне [-1, 1]

    // Генерация случайного числа и возвращение его
    return dis(gen);

}

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows&& y >= 0 && y < cols;
}

// Функция для выполнения поиска в ширину
std::pair<int, int> GameOfLife::bfs(std::vector<std::vector<Animal>> animalCells, std::vector<std::vector<int>> grid, int startX, int startY, int curSex,int & dir_x,int & dir_y) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Массив для отслеживания посещенных клеток
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Очередь для BFS
    std::queue < std::pair<int,int >> q;

    // Добавляем начальную клетку в очередь и отмечаем её как посещённую
    q.push(std::make_pair(startX, startY));
    visited[startX][startY] = true;

    // Массив смещений для соседних клеток (вправо, влево, вверх, вниз)
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };

    // Пока очередь не пуста
    while (!q.empty()) {
        // Извлекаем клетку из очереди
        std::pair<int,int> current = q.front();
        q.pop();

        // Выводим координаты текущей клетки (или делаем что-то другое)
        //cout << "Посетили клетку: (" << current.x << ", " << current.y << ")" << endl;

        // Просматриваем соседние клетки
        for (int i = 0; i < 4; ++i) {
            int newX = current.first + dx[i];
            int newY = current.second + dy[i];

            // Проверяем, что новая клетка находится в пределах поля и не посещалась
            if (isValid(newX, newY, rows, cols) && !visited[newX][newY] && grid[newX][newY] == 0) {
                // Добавляем новую клетку в очередь и отмечаем её как посещённую
                if (grid[newX][newY] == IS_HERBIVORE) {
                    if (animalCells[newX][newY].getSex() != curSex) {
                        if (startX - newX > 0) {
                            dir_x = -1;
                        }
                        else if (startX - newX < 0) {
                            dir_x = 1;
                        }
                        else {
                            dir_x = 0;
                        }
                        if (startY - newY > 0) {
                            dir_y = -1;
                        }   
                        else if (startY - newY < 0) {
                            dir_y = 1;
                        }
                        else {
                            dir_y = 0;
                        }
                        return std::make_pair(dir_x, dir_y);
                    }
                }
                q.push(std::make_pair(newX, newY));
                visited[newX][newY] = true;
            }
        }
    }
    return std::make_pair(0, 0);
}