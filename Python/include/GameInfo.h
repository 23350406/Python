
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

class Player
{
    string _color;
    string _username;
    bool _isPlayer;
    char _up    = 'w';
    char _down  = 's';
    char _left  = 'a';
    char _right = 'd';
public:
    bool   Check_isPlayer();
    string GetUsername();
    string GetColor();
    char   GetMove(string move);

	void SetUsername(string username);
	void SetColor(string color);
	void SetMove(string moveName, char letterMove);
	
};

class Cell
{
   string _typeCell;

public:
   string GetType();
   void   SetType(string type);
};
class Field
{
    int _height;
    int _width;
    vector<Cell*> _line;
    int _countPlayers;
    int _countBots;
    vector<Player> _team;
public:
    int GetHeight();
    int GetWidth();
	vector<Cell*> GetLine();
    vector<Player> GetTeam();

	void SetHeight(int height);
	void SetWidth(int width);
	void SetLine(vector<Cell*> line);
    void SetTeam(vector<Player> team);

};


class Snake
{
    int _head_x;
    int _head_y;
    int _tail_x;
    int _tail_y;
    string _direction;
public:
    int GetxHead();
    int GetyHead();
    int GetxTail();
    int GetyTail();
    string GetDirection();

	void SetxHead(int head_x);
	void SetyHead(int head_y);
	void SetxTail(int tail_x);
	void SetyTail(int tail_y);
	void SetDirection(string direction);
};

#endif // GAMEINFO_HPP