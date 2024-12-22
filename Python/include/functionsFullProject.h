
#ifndef FULL_H
#define FULL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <thread>

using std::vector;
using std::string;

class GameInfo {
private:
	int _numberOfRounds;
	int _numberOfBots;
	std::string _mapSize;

	bool _somethingIsPressed;
	std::string _currentWindowName;
public:

	// Конструктор по умолчанию.
	GameInfo();

	// Функция возвращает количество раундов в игре.
	int GetNumberOfRounds();

	// Функция увеличивает количество раундов в игре.
	void IncreaseNumberOfRounds();

	// Функция уменьшает количство раундов в игре.
	void DecreaseNumberOfRounds();

	// Функция возвращает количество ботов в игре.
	int GetNumberOfBots();

	// Функция увеличивает количество ботов в игре.
	void IncreaseNumberOfBots();

	// Функция уменьшает количетсов ботов в игре.
	void DecreaseNumberOfBots();

    // Функция вернёт карту игры
	std::string GetMapSize();

    // Функция для того, чтобы сменить карту игры на большую
	void IncreaseMapSize();

    // Функция для того, чтобы сменить карту игры на меньшую
	void DecreaseMapSize();

    // Функция, отлавливающая нажатаю кнопку
	bool GetPressedButton();

	// Функция, устанавливающая кнопку по умолчанию
	void SetPressedButton();

    // Функция отжимает кнопку в классе.
	void UnsetPressedButton();

    // Функция возвращает название текущего экрана.
	std::string GetCurrentWindowName();

    // Функция устанавливает название текущего экрана.
	void SetCurrentWindowName(std::string newWindowName);
};

class Cell
{
   sf::Image _imageCell;
   bool _isBusy;

public:
    Cell();
    Cell(sf::Image img, bool isBusy);

    sf::Image GetImage();
    bool GetIsBusy();

    void SetIsBusy(bool busy);
    void   SetImage(sf::Image type);
};

class Player
{
    sf::Color _color;
    string _username;
    bool _isPlayer;
    char _up    = 'w';
    char _down  = 's';
    char _left  = 'a';
    char _right = 'd';
public:
    bool Check_isPlayer();
    string GetUsername();
    sf::Color GetColor();
    char GetMove(string moveName);

	void SetUsername(string username);
	void SetColor(int r, int g, int b);
	void SetMove(string moveName, char letterMove);
	
};

class Field
{
    int _height;
    int _width;
    vector<vector<Cell>> _field;
    int _countPlayers;
    int _countBots;
    void InitializeFrom(int height, int width, int _countPlayers, int _countBots);
    // vector<Player> _players;

public:
    Field(int height, int width, int _countPlayers, int _countBots);

    int GetHeight();
    int GetWidth();
	vector<vector<Cell>> GetField();
    vector<Player> GetTeam();
    int GetCountPlayers();
    int GetCountBots();

	void SetHeight(int height);
	void SetWidth(int width);
	void SetLine(vector<vector<Cell>> line);
    void SetTeam(vector<Player> team);
    void SetCountBots(int countBots);
    void SetCountPlayers(int countPlayers);

};

class Snake
{
    int _head_x;
    int _head_y;
    int _tail_x;
    int _tail_y;
    string _direction;
    vector<std::pair<int, int>> _body; // pair хранит 2 типа как 1 с ключами first, second  порядок важен
public:
    Snake(int startX, int startY, string direction);

    int GetxHead();
    int GetyHead();
    int GetxTail();
    int GetyTail();
    string GetDirection();
    vector<std::pair<int, int>> GetBody();

	void SetxHead(int head_x);
	void SetyHead(int head_y);
	void SetxTail(int tail_x);
	void SetyTail(int tail_y);
    void SetDirection(string newDirection);

    void MoveSnake();
    void Grow();
    
};

// Функция определяет: является ли действие нажатием на левую кнопку мыши.
bool isLMC(sf::Event& event, GameInfo& gameInfo);

// Функция определяет: было ли действие в прямоугольнике заданном координатами.
bool isInBox(sf::Event& event, int x1, int y1, int x2, int y2);

void ChangeWindowToStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo);

void ChangeWindowToMainMenuWindow(sf::RenderWindow& window, GameInfo& gameInfo);

void ChangeWindowToLeaveGameWindow(sf::RenderWindow& window, GameInfo& gameInfo);

void ChangeWindowToSettingsWindow(sf::RenderWindow& window, GameInfo& gameInfo);

void ChangeWindowToAuthorsWindow(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция обрабатывает событие на экране главного меню.
void ProcessActionInMainMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция обрабатывает событие в меню начала игры.
void ProcessActionInStartGameMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция обрабатывает событие в меню начала игры.
void ProcessActionInLeaveGameMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция обрабатывает событие в меню настроек.
void ProcessActionInSettingsMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция обрабатывает событие в меню настроек.
void ProcessActionInAuthorsMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция обрабатывает событие.
void ProcessEvent(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит на размер карты.
void DrawMapSize(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow& window);

// Функция выводит в запись окно начального меню.
void DrawMainMenuWindow(sf::RenderWindow& window);

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит в запись окно начального меню.
void DrawLeaveGameWindow(sf::RenderWindow& window);

// Функция выводит экран настроек старта игры.
void DrawSettingsWindow(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит экран разработчиков.
void DrawAuthorsWindow(sf::RenderWindow& window);

// Функция выведет карту игры
void DrawMap(sf::RenderWindow& window, GameInfo& gameInfo, Field& field);

// Функция осуществляет переход с экрана главного меню на экран начала игры.
void MoveWindowFromMainToStart(sf::RenderWindow& window);

// Функция осуществляет переход с экрана начала игры на экран главного меню.
void MoveWindowFromStartToMain(sf::RenderWindow& window);

// Функция осуществляет переход с экрана главного меню на экран выхода из игры.
void MoveWindowFromMainToLeaveGame(sf::RenderWindow& window);

// Функция осуществляет переход с экрана выхода из игры на экран главного меню.
void MoveWindowFromLeaveGameToMain(sf::RenderWindow& window);

// Функция осуществляет переход с экрана главного меню на экран настроек игры.
void MoveWindowFromMainToSettings(sf::RenderWindow& window);

// Функция осуществляет переход с экрана настроек игры на экран главного меню.
void MoveWindowFromSettingsToMain(sf::RenderWindow& window);

// Функция осуществляет переход с экрана главного меню на экран авторов игры.
void MoveWindowFromMainToAuthors(sf::RenderWindow& window);

// Функция осуществляет переход с экрана авторов игры на экран главного меню.
void MoveWindowFromAuthorsToMain(sf::RenderWindow& window);

// Функция создаст размеры карты, в зависимости от выбранного размера карты
int DefineMapSize(string size);

// Функция создаст карту игры
vector<int> DefineParametersForField (GameInfo& gameInfo);

// Функция создаст рандомные значения
vector<int> GenerateRandomValues(int maxSize);

#endif // FULL_H