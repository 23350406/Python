
#ifndef FULL_H
#define FULL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
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

    //TODO: Дописать коммент
	void UnsetPressedButton();

    //TODO: Дописать коммент
	std::string GetCurrentWindowName();

    //TODO: Дописать коммент
	void SetCurrentWindowName(std::string newWindowName);
};

// Функция определяет: является ли действие нажатием на левую кнопку мыши.
bool isLMC(sf::Event& event, GameInfo& gameInfo);

// Функция определяет: было ли действие в прямоугольнике заданном координатами.
bool isInBox(sf::Event& event, int x1, int y1, int x2, int y2);

void ChangeWindowToStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo);

void ChangeWindowToMainMenuWindow(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция обрабатывает событие на экране главного меню.
void ProcessActionInMainMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

void ProcessActionInStartGameMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

void ProcessEvent(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo);

// Функция выводит кнопку "старт" в запись.
void DrawStartButton(sf::RenderWindow& window);

// Функция выводит кнопку "настройки" в запись.
void DrawSettingsButton(sf::RenderWindow& window);

// Функция выводит кнопку "выйти" в запись.
void DrawLeaveButton(sf::RenderWindow& window);

// Функция выводит кнопку "авторы" в запись.
void DrawAuthorsButton(sf::RenderWindow& window);

// На экран выводится селектор количества чего-то (раундов/ботов) со смещением на x и y пикселей от верхнего левого угла экрана.
void DrawSelector(sf::RenderWindow& window, int x, int y);

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит на размер карты.
void DrawMapSize(sf::RenderWindow& window, GameInfo& gameInfo);

// Функция выводит кнопку "играть" в запись.
void DrawPlayButton(sf::RenderWindow& window);

// На экран выводится заголовок счетчика раундов.
void DrawRoundsHeader(sf::RenderWindow& window);

// На экран выводится заголовок счетчика ботов.
void DrawBotsHeader(sf::RenderWindow& window);

// На экран выводится заголовок выбора карты.
void DrawMapHeader(sf::RenderWindow& window);

void DrawReturnArrow(sf::RenderWindow& window);

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow& window);

// Функция выводит в запись окно начального меню.
void DrawMainMenuWindow(sf::RenderWindow& window);

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo);


#endif // FULL_H