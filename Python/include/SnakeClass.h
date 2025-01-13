#include "functionsFullProject.h"

Snake::Snake(int startX, int startY, std::pair<float, float> startDirection)
{
    _head_x = startX;
    _head_y = startY;
    _direction = startDirection;
    _body.push_back({startX, startY});
}

int Snake::GetxHead() { return _head_x; }

int Snake::GetyHead() { return _head_y; }

int Snake::GetxTail() { return _tail_x; }

int Snake::GetyTail() { return _tail_y; }

std::pair<float, float> Snake::GetDirection() { return _direction; }

std::pair<float, float> Snake::GetBody(int partNumber) 
{
    return (partNumber < _body.size()) ? _body[partNumber] : _body[0];
}

void Snake::SetxHead(int head_x) { _head_x = head_x; }

void Snake::SetyHead(int head_y) { _head_y = head_y; }

void Snake::SetxTail(int tail_x) { _tail_x = tail_x; }

void Snake::SetyTail(int tail_y) { _tail_y = tail_y; }

// Изменяет направление движения змейки
void Snake::SetDirection(float x, float y)
{
    _direction.first = x;
    _direction.second = y;
}

void Snake::MoveSnake() {
    // Проверка прошедшего времени
    if (clock.getElapsedTime().asSeconds() >= moveSpeed) {
        // Сначала добавляем новую голову в начало тела змейки
        _body.insert(_body.begin(), {_body[0].first + _direction.first, _body[0].second + _direction.second});

        // Удаляем хвост (последнюю часть змейки)
        _body.pop_back();

        // Сброс времени
        clock.restart();
    }
}

void Snake::Grow() {
    // Добавляем новый сегмент в хвост змейки
    std::pair<float, float> newSegment = _body.back();
    _body.push_back(newSegment);
}
