
#ifndef FULL_H
#define FULL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
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

#endif // FULL_H