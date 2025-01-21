
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

class PlayerInfo {
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

class GameInfo {
private:
	int _numberOfRounds;
	int _numberOfBots;
	std::string _mapSize;
	bool _isSolo;

	bool _somethingIsPressed;
	std::string _currentWindowName;

	PlayerInfo _firstPlayerInfo;
	PlayerInfo _secondPlayerInfo;

	std::string _fieldInUse;
public:

	// Конструктор по умолчанию.
	GameInfo();

	// Функция устанавливает значение на игру для двоих.
	void SetDuo();

	// Функция устанавливает значение на игру для одного.
	void SetSolo();

	// Функция возвращает: сколько человек играет.
	bool GetIsSolo();

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

    // Функция возвращает размер игрового поля.
	std::string GetMapSize();

    // Функция для того, чтобы сменить карту игры на большую.
	void IncreaseMapSize();

    // Функция для того, чтобы сменить карту игры на меньшую.
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
};

// Функция создает первого игрока.
PlayerInfo CreateFirstPlayer();

// Функция создает второго игрока.
PlayerInfo CreateSecondPlayer();

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

// Функция возвращает строковую запись кнопки с клавиатуры.
std::string GetKeyboardCharacter(sf::Keyboard::Key key);

// Функция возвращает нажатую кнопку клавиатуры.
sf::Keyboard::Key GetPressedKey();

// Функция проверяет, что клавиша не используется в управлении.
bool keyIsntUsed(GameInfo& gameInfo, sf::Keyboard::Key keyToUse);

#endif // FULL_H
