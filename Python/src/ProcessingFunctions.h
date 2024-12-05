#pragma once

#include "DrawingFunctions.h"

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
