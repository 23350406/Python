#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

// Класс, содержащий информацию об игре.
class GameInfo {
private:
	int _numberOfRounds;
	int _numberOfBots;
	std::string _mapSize;

	bool _somethingIsPressed;
	std::string _currentWindowName;
public:

	// Конструктор по умолчанию.
	GameInfo() {
		_numberOfRounds = 1;
		_numberOfBots = 0;
		_mapSize = "medium";

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

	std::string GetMapSize() {
		return _mapSize;
	}

	void IncreaseMapSize() {
		if (_mapSize == "medium") {
			_mapSize = "large";
		}
		if (_mapSize == "small") {
			_mapSize = "medium";
		}
	}

	void DecreaseMapSize() {
		if (_mapSize == "medium") {
			_mapSize = "small";
		}
		if (_mapSize == "large") {
			_mapSize = "medium";
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
