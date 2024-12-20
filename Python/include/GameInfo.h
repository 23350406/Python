
#ifndef GAMEINFO_HPP
#define GAMEINFO_HPP

#include "functionsFullProject.h"
#include <vector>
#include <list>

using std::vector;
using std::string;

// Конструктор по умолчанию.
GameInfo::GameInfo() {
	_numberOfRounds = 1;
	_numberOfBots = 0;
	_mapSize = "medium";
	_somethingIsPressed = false;

	// Задается название открытого сейчас окна.
	_currentWindowName = "MainMenu";
}

// Функция возвращает количество раундов в игре.
int GameInfo::GetNumberOfRounds() {
	return _numberOfRounds;
}

// Функция увеличивает количество раундов в игре.
void GameInfo::IncreaseNumberOfRounds() {
	if (_numberOfRounds < 9) {
		++_numberOfRounds;
	}
}

// Функция уменьшает количство раундов в игре.
void GameInfo::DecreaseNumberOfRounds() {
	if (_numberOfRounds > 1) {
		--_numberOfRounds;
	}
}

// Функция возвращает количество ботов в игре.
int GameInfo::GetNumberOfBots() {
	return _numberOfBots;
}

// Функция увеличивает количество ботов в игре.
void GameInfo::IncreaseNumberOfBots() {
	if (_numberOfBots < 3) {
		++_numberOfBots;
	}
}

// Функция уменьшает количетсов ботов в игре.
void GameInfo::DecreaseNumberOfBots() {
	if (_numberOfBots > 0) {
		--_numberOfBots;
	}
}

//  TODO: Комментарии
std::string GameInfo::GetMapSize() {
	return _mapSize;
}

void GameInfo::IncreaseMapSize() {
	if (_mapSize == "medium") {
		_mapSize = "large";
	}
	if (_mapSize == "small") {
		_mapSize = "medium";
	}
}


void GameInfo::DecreaseMapSize() {
	if (_mapSize == "medium") {
		_mapSize = "small";
	}
	if (_mapSize == "large") {
		_mapSize = "medium";
	}
}

bool GameInfo::GetPressedButton() {
	return _somethingIsPressed;
}

void GameInfo::SetPressedButton() {
	_somethingIsPressed = true;
}

void GameInfo::UnsetPressedButton() {
	_somethingIsPressed = false;
}

std::string GameInfo::GetCurrentWindowName() {
	return _currentWindowName;
}

void GameInfo::SetCurrentWindowName(std::string newWindowName) {
	_currentWindowName = newWindowName;
}

#endif // GAMEINFO_HPP