#include "functionsFullProject.h"

Snake::Snake(int startX, int startY, string startDirection)
{
    _head_x = startX;
    _head_y = startY;
    _direction = startDirection;

    _body.push_back({_head_x, _head_y});
}

int Snake::GetxHead() { return _head_x; }

int Snake::GetyHead() { return _head_y; }

int Snake::GetxTail() { return _tail_x; }

int Snake::GetyTail() { return _tail_y; }

string Snake::GetDirection() { return _direction; }

vector<std::pair<int, int>> Snake::GetBody() { return _body; }

void Snake::SetxHead(int head_x) { _head_x = head_x; }

void Snake::SetyHead(int head_y) { _head_y = head_y; }

void Snake::SetxTail(int tail_x) { _tail_x = tail_x; }

void Snake::SetyTail(int tail_y) { _tail_y = tail_y; }

// Изменяет направление движения змейки
void Snake::SetDirection(string newDirection)
{
    if ((newDirection == "up" && _direction != "down") ||
        (newDirection == "down" && _direction != "up") ||
        (newDirection == "left" && _direction != "right") ||
        (newDirection == "right" && _direction != "left"))
    {
        _direction = newDirection;
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
    _body.push_back({_tail_x, _tail_y});
}
