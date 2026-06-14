#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

//настройки поля

// Размер поля 10x10 
const int GRID_SIZE = 10;

// Размер клетки в пикселях
const int CELL_SIZE = 60;

// Размер окна
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

//тип клеток

enum CellType
{
    EMPTY,      // пустая клетка
    OBSTACLE,   // препятствие
    START,      // старт
    END,        // финиш
    PATH,       // найденный путь
    VISITED     // посещённая клетка
};


struct Cell
{
    // Координаты клетки
    int x;
    int y;

    // Тип клетки
    CellType type;

    // Переменные алгоритма A*
    int g; // расстояние от старта
    int h; // эвристика
    int f; // g + h

    // Родительская клетка
    Cell* parent;

    Cell(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;

        type = EMPTY;

        g = 0;
        h = 0;
        f = 0;

        parent = nullptr;
    }
};



int heuristic(const Cell& a, const Cell& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

//проверка границ поля

bool isValid(int x, int y)
{
    return x >= 0 &&
        x < GRID_SIZE &&
        y >= 0 &&
        y < GRID_SIZE;
}

//для хранения клетки и её стоимости f, а также priority_queue работала как очередь с минимальным приоритетом
struct Node
{
    int f;
    Cell* cell;

    bool operator<(const Node& other) const
    {
        return f > other.f;
    }
};

//создание пустого поля 
vector<vector<Cell>> createGrid()
{
    //двумерный вектор, который будет хранить все клетки поля
    vector<vector<Cell>> grid;

    // внешний цикл создаёт строки поля
    for (int x = 0; x < GRID_SIZE; x++)
    {
        // временный вектор для одной строки
        vector<Cell> row;

        // внутренний цикл создаёт клетки в строке
        for (int y = 0; y < GRID_SIZE; y++)
        {
            // создаём клетку с координатами (x, y) и добавляем её в строку
            row.push_back(Cell(x, y));
        }
        // после заполнения строки добавляем её в поле
        grid.push_back(row);
    }
    // возвращаем готовую сетку
    return grid;
}

//восстановление пути
void reconstructPath(Cell* endCell)
{
    // Начинаем с клетки перед финишем
    Cell* current = endCell->parent;

    // Пока не дошли до старта
    while (current != nullptr &&
        current->type != START)
    {
        // Отмечаем клетку как часть пути
        current->type = PATH;
        // Переходим к предыдущей клетке маршрута
        current = current->parent;
    }
}

// алгоритм А
bool AStar(vector<vector<Cell>>& grid,
    Cell* start,
    Cell* finish)
{
    // Очередь с приоритетом.
    // В ней хранятся клетки, которые ещё нужно проверить.
    // Вершина с минимальным f будет извлекаться первой.
    
    priority_queue<Node> openSet;

    start->g = 0;//расстояние от старта до самого себя равно 0
    start->h = heuristic(*start, *finish);// вычисляем примерное расстояние
    start->f = start->g + start->h; // полная стоимость вершины

    openSet.push({ start->f, start });// добавляем стартовую клутку в открытый список

    //пока есть клетки для проверки
    while (!openSet.empty())
    {
        // Берём клетку с минимальным f
        Cell* current = openSet.top().cell;
        openSet.pop();

        // Если дошли до цели
        if (current == finish)
        {
            reconstructPath(finish);//восстанавливаем путь
            return true;
        }

        // Помечаем как посещённую, старт не перекрашиваем
        if (current->type != START)
        {
            current->type = VISITED;
        }

        // Смещения для соседей:
        // вправо, влево, вниз, вверх
        int dx[4] = { 1, -1, 0, 0 };
        int dy[4] = { 0, 0, 1, -1 };

        // Проверяем всех соседей
        for (int i = 0; i < 4; i++)
        {
            //координаты соседа
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            //если вышли за поле
            if (!isValid(nx, ny))
                continue;
            //получаем указатель на соседнюю клетку
            Cell* neighbor = &grid[nx][ny];

            //если это стена то переход не возможен
            if (neighbor->type == OBSTACLE)
                continue;

            //каждый переход стоит 1 шаг, пожтому расстояние до соседа будет +1
            int newG = current->g + 1;

            //проверка найден ли лучший путь
            if (neighbor->parent == nullptr ||
                newG < neighbor->g)
            {
                //запоминаем откуда пришли в клетку
                neighbor->parent = current;

                //обновляем стоимость пути
                neighbor->g = newG;
                //вычисляем расстояние
                neighbor->h = heuristic(*neighbor, *finish);
                neighbor->f = neighbor->g + neighbor->h;//полная стоимость

                //добавляем клетку в открытый список
                openSet.push(
                    {
                        neighbor->f,
                        neighbor
                    });
            }
        }
    }
    //если путь не найден
    return false;
}

// поле для варианта 11
void loadVariant11(vector<vector<Cell>>& grid)
{
    // Координаты всех стен лабиринта
    vector<pair<int, int>> walls =
    {
        {0,0},{1,0},{5,0},
        {0,1},{1,1},{3,1},{6,1},
        {0,2},{1,2},{4,2},{6,2},
        {1,3},{6,3},
        {7,4},
        {0,5},{1,5},{6,5},
        {1,6},{5,6},
        {1,7},{3,7},{7,7},
        {5,8},
        {4,9}
    };

    // Проходим по всем координатам стен
    for (auto wall : walls)
    {
        // Меняем тип клетки на препятствие
        grid[wall.first][wall.second].type =
            OBSTACLE;
    }
}

// генерация случайного поля 
void generateRandomField(vector<vector<Cell>>& grid)
{
    random_device rd;
    // Генератор случайных чисел
    mt19937 gen(rd());

    // Случайное число от 0 до 99
    uniform_int_distribution<> dist(0, 99);

    // Проходим по всему полю
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            // Делаем клетку пустой
            grid[x][y].type = EMPTY;
            // Удаляем старую информацию о пути
            grid[x][y].parent = nullptr;

            // 20% препятствий
            if (dist(gen) < 20)
            {
                grid[x][y].type = OBSTACLE;
            }
        }
    }
}

// отрисовка поля
void drawGrid(RenderWindow& window,
    vector<vector<Cell>>& grid)
{
    // Проходим по всем клеткам
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            // Создаём прямоугольник для отображения клетки
            RectangleShape cell(
                Vector2f(
                    CELL_SIZE - 1,
                    CELL_SIZE - 1
                )
            );

            // Устанавливаем координаты клетки
            cell.setPosition(
                (float)(x * CELL_SIZE),
                (float)(y * CELL_SIZE)
            );

            // Выбираем цвет в зависимости от типа клетки
            switch (grid[x][y].type)
            {
            case EMPTY:
                cell.setFillColor(Color::White);
                break;

            case OBSTACLE:
                cell.setFillColor(Color::Black);
                break;

            case START:
                cell.setFillColor(Color(76, 187, 23)); 
                break;

            case END:
                cell.setFillColor(Color(72, 6, 7)); 
                break;
                 
            case PATH:
                cell.setFillColor(Color::Blue);
                break;

            case VISITED:
                cell.setFillColor(Color::Cyan);
                break;
            }

            window.draw(cell);
        }
    }
}


int main()
{
    // Инициализация генератора случайных чисел текущим временем
    srand((unsigned int)time(0));

    // Создание окна с размером WINDOW_SIZE x WINDOW_SIZE пикселей
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE),
        "A* Algorithm"
    );

    // Создаём пустое поле (двумерный вектор Cell)
    vector<vector<Cell>> grid = createGrid();

    // Загружаем предопределённую конфигурацию стен (вариант №11)
    loadVariant11(grid);

    // Устанавливаем указатели на старт (ячейка [0][4]) и финиш ([9][9])
    Cell* start = &grid[0][4];
    Cell* finish = &grid[9][9];

    start->type = START;   // тип ячейки – начало пути
    finish->type = END;    // тип ячейки – цель

    // Главный цикл обработки событий и отрисовки
    while (window.isOpen())
    {
        Event event;

        // Обработка всех накопившихся событий в очереди
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            // Нажатие SPACE: запуск A* 
            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Space)
            {
                // Сброс визуальных меток PATH/VISITED в EMPTY
                // и очистка данных для повторного поиска пути
                for (int i = 0; i < GRID_SIZE; i++)
                    for (int j = 0; j < GRID_SIZE; j++)
                    {
                        if (grid[i][j].type == PATH ||
                            grid[i][j].type == VISITED)
                            grid[i][j].type = EMPTY;

                        grid[i][j].parent = nullptr;  // обнуляем ссылку на родителя
                        grid[i][j].g = 0;              // стоимость от старта
                        grid[i][j].h = 0;              // эвристика до финиша
                        grid[i][j].f = 0;              // g + h
                    }

                // Запуск алгоритма A* 
                AStar(grid, start, finish);
            }

            // Нажатие R: генерация случайного поля
            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::R)
            {
                bool valid = false;   // существует ли путь?

                do
                {
                    // Создаём новое пустое поле
                    grid = createGrid();
                    // Генерируем случайные стены
                    generateRandomField(grid);

                    // Случайные координаты старта и финиша (разные, не стены)
                    int sx, sy, gx, gy;
                    do
                    {
                        sx = rand() % GRID_SIZE;
                        sy = rand() % GRID_SIZE;
                        gx = rand() % GRID_SIZE;
                        gy = rand() % GRID_SIZE;
                    } while ((sx == gx && sy == gy) ||
                        grid[sx][sy].type == OBSTACLE ||
                        grid[gx][gy].type == OBSTACLE);

                    start = &grid[sx][sy];
                    finish = &grid[gx][gy];

                    start->type = START;
                    finish->type = END;

                    // Сброс данных для A* (как и при SPACE)
                    for (int i = 0; i < GRID_SIZE; i++)
                        for (int j = 0; j < GRID_SIZE; j++)
                        {
                            grid[i][j].parent = nullptr;
                            grid[i][j].g = 0;
                            grid[i][j].h = 0;
                            grid[i][j].f = 0;
                        }

                    // Проверяем, есть ли путь (valid = true/false)
                    valid = AStar(grid, start, finish);

                    // Если путь найден – убираем временные метки PATH/VISITED,
                    // оставляя только старт, финиш и стены
                    if (valid)
                    {
                        for (int i = 0; i < GRID_SIZE; i++)
                            for (int j = 0; j < GRID_SIZE; j++)
                                if (grid[i][j].type == PATH ||
                                    grid[i][j].type == VISITED)
                                    grid[i][j].type = EMPTY;

                        start->type = START;
                        finish->type = END;
                    }
                } while (!valid);   // повторяем, пока не получим решаемую карту

                // Вывод координат старта и финиша в консоль
                cout << "Random map generated!" << endl;
                cout << "Start: (" << start->x << "," << start->y << ") ";
                cout << "End: (" << finish->x << "," << finish->y << ")" << endl;
            }
        }

        // Отрисовка текущего состояния поля
        window.clear();
        drawGrid(window, grid);
        window.display();
    }

    return 0;
}