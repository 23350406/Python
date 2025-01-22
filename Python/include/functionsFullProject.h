#ifndef FULL_H
#define FULL_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

class PlayerInfo
{
private:
    std::string _playerName;
    sf::Keyboard::Key _up;
    sf::Keyboard::Key _left;
    sf::Keyboard::Key _right;
    sf::Keyboard::Key _down;
    sf::Color _playerColor;

public:
    // Функция задает имя игрока.
    void SetName(std::string newName);

    // Загрузка и сохранение информации о игроке
    void LoadFromFile(std::ifstream &inFile);
    void SaveToFile(std::ofstream &outFile) const;

    // Функция возвращает имя игрока.
    std::string GetName();

    // Функция задает значение клавиши для движения вверх.
    void SetUpKey(sf::Keyboard::Key newUp);

    // Функция возвращает значение клавиши для движения вверх.
    sf::Keyboard::Key GetUpKey();

    // Функция задает значение клавиши для движения вниз.
    void SetDownKey(sf::Keyboard::Key newDown);

    // Функция возвращает значение клавиши для движения вниз.
    sf::Keyboard::Key GetDownKey();

    // Функция задает значение клавиши для движения вправо.
    void SetRightKey(sf::Keyboard::Key newRight);

    // Функция возвращает значение клавиши для движения вправо.
    sf::Keyboard::Key GetRightKey();

    // Функция задает значение клавиши для движения влево.
    void SetLeftKey(sf::Keyboard::Key newLeft);

    // Функция возвращает значение клавиши для движения влево.
    sf::Keyboard::Key GetLeftKey();

    // Функция задает значение цвета игрока.
    void SetColor(sf::Color newColor);

    // Функция возвращает значение цвета игрока.
    sf::Color GetColor();
};

class GameInfo
{
private:
	int _numberOfRounds;
	int _numberOfBots;
	std::string _mapSize;
	bool _isSolo;
  int _currentRound;

    PlayerInfo _firstPlayerInfo;
    PlayerInfo _secondPlayerInfo;

    std::string _fieldInUse;

public:
    // Конструктор по умолчанию.
    GameInfo();

    // Функция увеличивает количество раундов в игре.
    void IncreaseNumberOfRounds();

    // Функция устанавливает значение на игру для двоих.
    void SetDuo();

    // Функция устанавливает значение на игру для одного.
    void SetSolo();

    // Функция возвращает: сколько человек играет.
    bool GetIsSolo();

  // Функция вернёт текущий раунд
  int GetCurrentRound();

  // Функция установит текущий раунд
  int SetCurrentRound(int currentRound);

	// Функция возвращает количество раундов в игре.
	int GetNumberOfRounds();

    PlayerInfo GetFirstPlayerInfo();

    void SetFirstPlayerInfo(PlayerInfo newInfo);

    PlayerInfo GetSecondPlayerInfo();

    void SetSecondPlayerInfo(PlayerInfo newInfo);

    std::string GetFieldInUse();

    void SetFieldInUse(std::string fieldName);

    void LoadFromFile(const std::string &filename);

    // Сохранение состояния в файл
    void SaveToFile(const std::string &filename) const;

    // Функция уменьшает количство раундов в игре.
    void DecreaseNumberOfRounds();

    // Функция возвращает количество ботов в игре.
    int GetNumberOfBots();

    // Функция увеличивает количество ботов в игре.
    void IncreaseNumberOfBots();

    // Функция уменьшает количетсов ботов в игре.
    void DecreaseNumberOfBots();

    // Функция, отлавливающая нажатаю кнопку
    bool GetPressedButton();

    // Функция возвращает размер игрового поля.
    std::string GetMapSize();

    // Функция для того, чтобы сменить карту игры на большую.
    void IncreaseMapSize();

    // Функция для того, чтобы сменить карту игры на меньшую.
    void DecreaseMapSize();

    // Функция, устанавливающая кнопку по умолчанию
    void SetPressedButton();

    // Функция отжимает кнопку в классе.
    void UnsetPressedButton();

    // Функция возвращает название текущего экрана.
    std::string GetCurrentWindowName();

    // Функция устанавливает название текущего экрана.
    void SetCurrentWindowName(std::string newWindowName);
};

// Перечисление типов ячеек
enum class CellType
{
    EMPTY,      // Пустая ячейка
    SNAKE_HEAD, // Голова змейки
    SNAKE_BODY, // Тело змейки
    SNAKE_TAIL, // Хвост змейки
    FOOD,       // Еда
    OBSTACLE,   // Препятствие
    SNAKE_HEAD_1,
    SNAKE_BODY_1,
    SNAKE_TAIL_1,
    SNAKE_HEAD_2,
    SNAKE_BODY_2,
    SNAKE_TAIL_2
};

class Cell
{
private:
    sf::Image _imageCell; // Картинка ячейки
    bool _isBusy;         // Флаг занятости ячейки
    CellType _type;       // Тип ячейки (пустая, змейка, еда и т.д.)

public:
    // Конструктор по умолчанию
    Cell();

    // Конструктор с параметрами
    Cell(sf::Image img, bool isBusy, CellType type = CellType::EMPTY);

    // Получить тип ячейки
    CellType GetType() const;

    // Установить тип ячейки
    void SetType(CellType type);

    // Получить изображение ячейки
    sf::Image GetImage();

    // Проверка на занятость ячейки
    bool GetIsBusy();

    // Установить занятость ячейки
    void SetIsBusy(bool busy);

    // Установить изображение ячейки
    void SetImage(const sf::Image &img);
};

class Snake {
private:
  std::vector<std::pair<int, int>>
      _body; // тело змейки, список пар координат (x, y)
  sf::Clock _clock;        // Часы для контроля времени
  float _moveSpeed = 0.16f; // Скорость движения змейки
  bool _grew = false; // Флаг для отслеживания, выросла ли змейка
  std::pair<int, int> _direction; // Направление движения змейки

public:
    Snake(int startX, int startY);

    std::vector<std::pair<int, int>> GetBody() const;

    // Логика роста змейки
    void Grow();

    // Перемещение змейки
    void MoveSnake(int fieldWidth, int fieldHeight);

    // Перемещение ботов
    void MoveBot(int fieldWidth, int fieldHeight);

    // Изменение направления змейки
    void ChangeDirection(const std::pair<int, int> &newDirection);

    std::pair<int, int> GetDirection() const { return _direction; }

    float GetMoveSpeed() { return _moveSpeed; }
};

class Field
{
private:
    int _height;
    int _width;
    std::vector<std::vector<Cell>> _field;

public:
    Field(int height, int width);

    int GetHeight() { return _height; }

    int GetWidth() { return _width; }

    std::vector<std::vector<Cell>> GetField() { return _field; }

    // Установить тип ячейки по координатам
    void SetCellType(int x, int y, CellType type) { _field[y][x].SetType(type); }

    // Установить еду на поле
    void SetFood(int x, int y) { _field[y][x].SetType(CellType::FOOD); }

    // Размещение препятствий
    void PlaceObstacles(int numberOfObstacles);

    // Размещение еды во время игры
    void PlaceFood();

    // Размещение еды в начале игры
    void PlaceFood(const std::vector<Snake> &snakes);

    // Движение с ботом
    void UpdateMap(const std::vector<Snake> &snakes);

    // Движение без бота
    void UpdateMap(const Snake &snake);

    // Движение в многопользовательской игре
    void UpdateMap(const Snake &snake1, const Snake &snake2);
};

// Функция ищет еду
bool FindApple(Field &field, int &appleX, int &appleY);

class Bot
{
public:
    // Конструктор перемещения
    Bot(Bot&& other) noexcept;

    // Оператор присваивания перемещением
    Bot& operator=(Bot&& other) noexcept;

    // Конструктор
    Bot(Snake &snake, Field &field) : _snake(&snake), _field(field) {}

    // Движение бота
    void Move();

    // Получение позиции головы змейки
    std::pair<int, int> GetHeadPosition() const ;

    // Геттер для змеи
    Snake& GetSnake() const { return *_snake;}

    // Геттер для поля
    Field &GetField() { return _field; }

private:
    Snake *_snake; // Указатель на объект змеи
    Field &_field; // Ссылка на объект поля

    // Ищем ближайшую еду
    std::pair<int, int> FindNearestFood(const std::pair<int, int>& head);

    // Двигаем бота случайным образом, если нет еды
    void MoveRandomly();
};

// Функция устанавливает название текущего экрана.
void SetCurrentWindowName(std::string newWindowName);

// Функция возвращает информацию о первом игроке.
PlayerInfo GetFirstPlayerInfo();

// Функция устанавливает информацию о первом игроке.
void SetFirstPlayerInfo(PlayerInfo newInfo);

// Функция возвращает информацию о втором игроке.
PlayerInfo GetSecondPlayerInfo();

// Функция устанавливает информацию о втором игроке.
void SetSecondPlayerInfo(PlayerInfo newInfo);

// Функция возвращает название изменяемого поля.
std::string GetFieldInUse();

// Функция устанавливает название изменяемого поля.
void SetFieldInUse(std::string fieldName);

// Функция создает первого игрока.
PlayerInfo CreateFirstPlayer();

// Функция создает второго игрока.
PlayerInfo CreateSecondPlayer();

// Функция определяет: является ли действие нажатием на левую кнопку мыши.
bool isLMC(sf::Event &event, GameInfo &gameInfo);

// Функция определяет: было ли действие в прямоугольнике заданном координатами.
bool isInBox(sf::Event &event, int x1, int y1, int x2, int y2);

void ChangeWindowToStartGameWindow(sf::RenderWindow &window,
                                   GameInfo &gameInfo);

void ChangeWindowToMainMenuWindow(sf::RenderWindow &window, GameInfo &gameInfo);

void ChangeWindowToLeaveGameWindow(sf::RenderWindow &window,
                                   GameInfo &gameInfo);

void ChangeWindowToSettingsWindow(sf::RenderWindow &window, GameInfo &gameInfo);

void ChangeWindowToAuthorsWindow(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция обрабатывает событие на экране главного меню.
void ProcessActionInMainMenu(sf::RenderWindow &window, sf::Event &event,
                             GameInfo &gameInfo);

// Функция обрабатывает событие в меню начала игры.
void ProcessActionInStartGameMenu(sf::RenderWindow &window, sf::Event &event,
                                  GameInfo &gameInfo);

// Функция обрабатывает событие в меню начала игры.
void ProcessActionInLeaveGameMenu(sf::RenderWindow &window, sf::Event &event,
                                  GameInfo &gameInfo);

// Функция обрабатывает событие в меню настроек.
void ProcessActionInSettingsMenu(sf::RenderWindow &window, sf::Event &event,
                                 GameInfo &gameInfo);

// Функция обрабатывает событие в меню настроек.
void ProcessActionInAuthorsMenu(sf::RenderWindow &window, sf::Event &event,
                                GameInfo &gameInfo);

// Функция обрабатывает событие.
void ProcessEvent(sf::RenderWindow &window, sf::Event &event,
                  GameInfo &gameInfo);

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция выводит на размер карты.
void DrawMapSize(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow &window);

// Функция выводит в запись окно начального меню.
void DrawMainMenuWindow(sf::RenderWindow &window);

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция выводит в запись окно начального меню.
void DrawLeaveGameWindow(sf::RenderWindow &window);

// Функция выводит экран настроек старта игры.
void DrawSettingsWindow(sf::RenderWindow &window, GameInfo &gameInfo);

// Функция выводит экран разработчиков.
void DrawAuthorsWindow(sf::RenderWindow &window);

// Функция выведет карту игры
void DrawMap(sf::RenderWindow &window, GameInfo &gameInfo, Field &field);

// Функция осуществляет переход с экрана главного меню на экран начала игры.
void MoveWindowFromMainToStart(sf::RenderWindow &window);

// Функция осуществляет переход с экрана начала игры на экран главного меню.
void MoveWindowFromStartToMain(sf::RenderWindow &window);

// Функция осуществляет переход с экрана главного меню на экран выхода из игры.
void MoveWindowFromMainToLeaveGame(sf::RenderWindow &window);

// Функция осуществляет переход с экрана выхода из игры на экран главного меню.
void MoveWindowFromLeaveGameToMain(sf::RenderWindow &window);

// Функция осуществляет переход с экрана главного меню на экран настроек игры.
void MoveWindowFromMainToSettings(sf::RenderWindow &window);

// Функция осуществляет переход с экрана настроек игры на экран главного меню.
void MoveWindowFromSettingsToMain(sf::RenderWindow &window);

// Функция осуществляет переход с экрана главного меню на экран авторов игры.
void MoveWindowFromMainToAuthors(sf::RenderWindow &window);

// Функция осуществляет переход с экрана авторов игры на экран главного меню.
void MoveWindowFromAuthorsToMain(sf::RenderWindow &window);

// Функция создаст размеры карты, в зависимости от выбранного размера карты
int DefineMapSize(string size);

// Функция создаст карту игры
vector<int> DefineParametersForField(GameInfo &gameInfo);

// Функция создаст рандомные значения
vector<int> GenerateRandomValues(int maxSize);

// Функция реализует игровой процесс
void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &playerSnake, std::vector<Snake> &bots);

// Игровой процесс без ботов
void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field, Snake &snake);

// Игровой процесс многопользовательской игры
void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field, Snake &snake1, Snake &snake2);

// Функция возвращает строковую запись кнопки с клавиатуры.
std::string GetKeyboardCharacter(sf::Keyboard::Key key);

// Функция возвращает нажатую кнопку клавиатуры.
sf::Keyboard::Key GetPressedKey();

// Функция проверяет, что клавиша не используется в управлении.
bool keyIsntUsed(GameInfo &gameInfo, sf::Keyboard::Key keyToUse);

// Функция вернёт цвет змейки
std::string ChoiceSelection(sf::Color color);

#endif // FULL_H
