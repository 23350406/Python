// pythonUpdate.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

// Библиотека, чтобы узнавать размер экрана пользователя.
#include <windows.h>

// Класс, содержащий информацию об игре.
class GameInfo {
private:
	int _numberOfRounds;
	int _numberOfBots;
	
	bool _somethingIsPressed;
	std::string _currentWindowName;
public:

	// Конструктор по умолчанию.
	GameInfo() {
		_numberOfRounds = 1;
		_numberOfBots = 0;
		_somethingIsPressed = false;

		// Задается название открытого сейчас окна.
		_currentWindowName = "MainMenu";
	}
	
	// Функция возвращает количество раундов в игре.
	int GetNumberOfRounds() {
		return _numberOfRounds;
	}

	// Функция увеличивает количество раундов в игре.
	void IncreaseNumberOfRounds() {
		if (_numberOfRounds < 9) {
			++_numberOfRounds;
		}
	}

	// Функция уменьшает количство раундов в игре.
	void DecreaseNumberOfRounds() {
		if (_numberOfRounds > 1) {
			--_numberOfRounds;
		}
	}

	// Функция возвращает количество ботов в игре.
	int GetNumberOfBots() {
		return _numberOfBots;
	}

	// Функция увеличивает количество ботов в игре.
	void IncreaseNumberOfBots() {
		if (_numberOfBots < 3) {
			++_numberOfBots;
		}
	}

	// Функция уменьшает количетсов ботов в игре.
	void DecreaseNumberOfBots() {
		if (_numberOfBots > 0) {
			--_numberOfBots;
		}
	}

	bool GetPressedButton() {
		return _somethingIsPressed;
	}

	void SetPressedButton() {
		_somethingIsPressed = true;
	}

	void UnsetPressedButton() {
		_somethingIsPressed = false;
	}

	std::string GetCurrentWindowName() {
		return _currentWindowName;
	}

	void SetCurrentWindowName(std::string newWindowName) {
		_currentWindowName = newWindowName;
	}
};

// Функция выводит кнопку "старт" в запись.
void DrawStartButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/start.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 50);
	window.draw(buttonSprite);
}

// Функция выводит кнопку "настройки" в запись.
void DrawSettingsButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/settings.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 242);

	window.draw(buttonSprite);
}

// Функция выводит кнопку "выйти" в запись.
void DrawLeaveButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/leave.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 434);

	window.draw(buttonSprite);
}

// Функция выводит кнопку "авторы" в запись.
void DrawAuthorsButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/authors.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(1012, 508);

	window.draw(buttonSprite);
}

// Функция выводит в запись окно начального меню.
void DrawMainMenuWindow(sf::RenderWindow& window) {
	
	// В запись заносится кнопка "старт".
	DrawStartButton(window);

	// В запись заносится кнопка "настройки".
	DrawSettingsButton(window);

	// В запись заносится кнопка "выйти".
	DrawLeaveButton(window);

	// В запись заносится кнопка "авторы".
	DrawAuthorsButton(window);
}

// На экран выводится селектор количества чего-то (раундов/ботов) со смещением на x и y пикселей от верхнего левого угла экрана.
void DrawSelector(sf::RenderWindow& window, int x, int y) {

	// На экран выводится стрелка для уменьшения числа раундов.
	sf::Texture leftArrowTexture;
	leftArrowTexture.loadFromFile("../../../images/left_arrow.png");
	sf::Sprite leftArrowSprite(leftArrowTexture);
	leftArrowSprite.setPosition(x, y);
	window.draw(leftArrowSprite);

	// На экран выводится панель счетчика раундов.
	sf::Texture selectCountTexture;
	selectCountTexture.loadFromFile("../../../images/select_count.png");
	sf::Sprite selectCountSprite(selectCountTexture);
	selectCountSprite.setPosition(x + 50, y);
	window.draw(selectCountSprite);

	// На экран выводится стрелка для увеличения количества раундов.
	sf::Texture rightArrowTexture;
	rightArrowTexture.loadFromFile("../../../images/right_arrow.png");
	sf::Sprite rightArrowSprite(rightArrowTexture);
	rightArrowSprite.setPosition(x + 200, y);
	window.draw(rightArrowSprite);
}

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfRounds()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(345, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfBots()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(796, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит кнопку "играть" в запись.
void DrawPlayButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/play.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 388);
	window.draw(buttonSprite);
}

// На экран выводится заголовок счетчика раундов.
void DrawRoundsHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/rounds_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(276, 70);
	window.draw(returnButtonSprite);
}

// На экран выводится заголовок счетчика ботов.
void DrawBotsHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/bots_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(726, 70);
	window.draw(returnButtonSprite);
}

// На экран выводится заголовок выбора карты.
void DrawMapHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/map_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(501, 194);
	window.draw(returnButtonSprite);
}

void DrawReturnArrow(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/return_arrow.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(10, 10);
	window.draw(returnButtonSprite);
}

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo) {

	// На экран выводится стрелка возвращения назад.
	DrawReturnArrow(window);

	// На экран выводится селектор раундов.
	DrawSelector(window, 226, 120);
	DrawNumberOfRounds(window, gameInfo);
	DrawRoundsHeader(window);

	// На экран выводится селектор ботов.
	DrawSelector(window, 676, 120);
	DrawNumberOfBots(window, gameInfo);
	DrawBotsHeader(window);

	// На экран выводится селектор ботов.
	DrawSelector(window, 451, 244);
	DrawMapHeader(window);

	// На экран выводится кнопка "играть".
	DrawPlayButton(window);
}

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow& window) {
	/*Создадим объект типа image и будем выгружать его в оконное приложение
	  Важно создавать объект, т.к. есть свойства, которые не всегда найдутся в текстуре.
	  К примеру маска цветов - можем игнорировать какие либо цвета объекта*/
	sf::Image pythonImage;
	pythonImage.loadFromFile("../../../images/pngwing.com.png");

	// Текстура и есть изображение. Можно не использовать Image (НО НЕЛЬЗЯ!!)
	sf::Texture pythonTexture;
	pythonTexture.loadFromImage(pythonImage);

	// Необходимо для выгрузки изображения в окно
	sf::Sprite pythonSprite;
	pythonSprite.setTexture(pythonTexture);
	pythonSprite.setPosition(20, 468);

	// На экран выводится змейка-талисман.
	window.draw(pythonSprite);
}

// Функция определяет: является ли действие нажатием на левую кнопку мыши.
bool isLMC(sf::Event& event, GameInfo& gameInfo) {
	// Если пользователь нажал не на мышку, то false.
	if (event.type != sf::Event::MouseButtonReleased) {
		return false;
	}

	// Если кнопка мыши не левая - false.
	if (event.mouseButton.button != sf::Mouse::Left) {
		return false;
	}

	// Если кнопка только нажалась - возвращается true.
	return true;
}

// Функция определяет: было ли действие в прямоугольнике заданном координатами.
bool isInBox(sf::Event& event, int x1, int y1, int x2, int y2) {
	return event.mouseButton.x >= x1 && event.mouseButton.x <= x2 && event.mouseButton.y >= y1 && event.mouseButton.y <= y2;
}

void ChangeWindowToMainMenuWindow(sf::RenderWindow& window, GameInfo& gameInfo) {
	// Записывается название экрана игры, на который перешел пользователь.
	gameInfo.SetCurrentWindowName("MainMenu");

	// Экран закрашивается черным.
	window.clear(sf::Color::Black);

	// В вывод на экран заносится главное меню.
	DrawMainMenuWindow(window);

	// В вывод на экран заносится змейка-талисман.
	DrawPythonTalisman(window);

	// Записанное в вывод показывается пользователю.
	window.display();
}

void ChangeWindowToStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo) {
	// Записывается название экрана игры, на который перешел пользователь.
	gameInfo.SetCurrentWindowName("StartGame");

	// Экран закрашивается черным.
	window.clear(sf::Color::Black);

	// В вывод на экран заносится экран выбора настроек старта игры.
	DrawStartGameWindow(window, gameInfo);

	// В вывод на экран заносится змейка-талисман.
	DrawPythonTalisman(window);

	// Записанное в вывод показывается пользователю.
	window.display();
}

// Функция обрабатывает событие на экране главного меню.
void ProcessActionInMainMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo) {
	// Если пользователь нажал ЛКМ.

	if (isLMC(event, gameInfo)) {

		if (gameInfo.GetPressedButton()) {
			return;
		}

		gameInfo.SetPressedButton();

		// Пользователь нажал ЛКМ на кнопку "START" -> переход на страницу настроек старта игры.
		if (isInBox(event, 426, 50, 726, 210)) {
			ChangeWindowToStartGameWindow(window, gameInfo);
		}

		return;
	}

	gameInfo.UnsetPressedButton();
}

void ProcessActionInStartGameMenu(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo) {

	// Если пользователь нажал ЛКМ.
	if (isLMC(event, gameInfo)) {

		if (gameInfo.GetPressedButton()) {
			return;
		}

		gameInfo.SetPressedButton();

		// Пользователь нажал ЛКМ на кнопку "START" -> переход на страницу настроек старта игры.
		if (isInBox(event, 10, 10, 90, 70)) {
			ChangeWindowToMainMenuWindow(window, gameInfo);
		}

		// Пользователь уменьшил количество раундов.
		if (isInBox(event, 226, 120, 276, 170)) {
			gameInfo.DecreaseNumberOfRounds();
			window.clear();
			DrawStartGameWindow(window, gameInfo);
			DrawPythonTalisman(window);
			window.display();
		}

		// Пользователь увеличил количество раундов.
		if (isInBox(event, 426, 120, 476, 170)) {
			gameInfo.IncreaseNumberOfRounds();
			window.clear();
			DrawStartGameWindow(window, gameInfo);
			DrawPythonTalisman(window);
			window.display();
		}

		// Пользователь уменьшил количество раундов.
		if (isInBox(event, 676, 120, 726, 170)) {
			gameInfo.DecreaseNumberOfBots();
			window.clear();
			DrawStartGameWindow(window, gameInfo);
			DrawPythonTalisman(window);
			window.display();
		}

		// Пользователь увеличил количество раундов.
		if (isInBox(event, 876, 120, 926, 170)) {
			gameInfo.IncreaseNumberOfBots();
			window.clear();
			DrawStartGameWindow(window, gameInfo);
			DrawPythonTalisman(window);
			window.display();
		}

		return;
	}

	gameInfo.UnsetPressedButton();
}

void ProcessEvent(sf::RenderWindow& window, sf::Event& event, GameInfo& gameInfo) {
	if (gameInfo.GetCurrentWindowName() == "MainMenu") {
		ProcessActionInMainMenu(window, event, gameInfo);
		return;
	}

	if (gameInfo.GetCurrentWindowName() == "StartGame") {
		ProcessActionInStartGameMenu(window, event, gameInfo);
		return;
	}
}

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
