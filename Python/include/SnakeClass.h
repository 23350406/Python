#include "functionsFullProject.h"

Snake::Snake(int startX, int startY, string startDirection)
{
    this->_head_x = startX;
    this->_head_y = startY;
    this->_direction = startDirection;

    this->_body.push_back({_head_x, _head_y});
}

int Snake::GetxHead() { return this->_head_x; }

int Snake::GetyHead() { return this->_head_y; }

int Snake::GetxTail() { return this->_tail_x; }

int Snake::GetyTail() { return this->_tail_y; }

string Snake::GetDirection() { return this->_direction; }

vector<std::pair<int, int>> Snake::GetBody() { return this->_body; }

void Snake::SetxHead(int head_x) { this->_head_x = head_x; }

void Snake::SetyHead(int head_y) { this->_head_y = head_y; }

void Snake::SetxTail(int tail_x) { this->_tail_x = tail_x; }

void Snake::SetyTail(int tail_y) { this->_tail_y = tail_y; }

// Изменяет направление движения змейки
void Snake::SetDirection(string newDirection)
{
    if ((newDirection == "up" && this->_direction != "down") ||
        (newDirection == "down" && this->_direction != "up") ||
        (newDirection == "left" && this->_direction != "right") ||
        (newDirection == "right" && this->_direction != "left"))
    {
        this->_direction = newDirection;
    }
}

// Движение змейки
void Snake::MoveSnake()
{
    // Сохраняем текущее положение головы, понадобится при разукрашевании клетки
    int prevX = _head_x;
    int prevY = _head_y;

    // Обновляем координаты головы в зависимости от направления
    if (_direction == "up")
    {
        _head_y--;
    }
    else if (_direction == "down")
    {
        _head_y++;
    }
    else if (_direction == "left")
    {
        _head_x--;
    }
    else if (_direction == "right")
    {
        _head_x++;
    }

    // Обновляем тело змейки
    if (!_body.empty())
    {
        // Сохраняем старую позицию головы
        _body.insert(_body.begin(), {_head_x, _head_y}); // Добавляем новую голову
        _body.pop_back();                                // Удаляем последний сегмент (хвост)
    }
    else
    {
        _body.push_back({_head_x, _head_y}); // Если тело пустое, добавляем только голову
    }
}

// Увеличивает длину змейки
void Snake::Grow()
{
    this->_body.push_back({this->_tail_x, this->_tail_y});
}
