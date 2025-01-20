#include "functionsFullProject.h"

Snake::Snake(int startX, int startY) {
  // Инициализация змейки (размещение в 3 клетки)
  _body.push_back({startX, startY});     // Голова
  _body.push_back({startX - 1, startY}); // Тело
  _body.push_back({startX - 2, startY}); // Тело
  _direction = {1, 0}; // Начальное направление - вправо
}

std::vector<std::pair<int, int>> Snake::GetBody() const { return _body; }

void Snake::Grow() {
  // Добавляем новую часть в хвост, которая будет иметь те же координаты, что и
  // текущий хвост
  std::pair<int, int> newTail =
      _body.back(); // Координаты последней части змейки
  _body.push_back(newTail); // Добавляем эту координату как новый сегмент
  _grew = true;             // Устанавливаем флаг роста
}

void Snake::MoveSnake(int fieldWidth, int fieldHeight) {
  // Добавляем новое положение головы
  std::pair<int, int> newHead = {_body[0].first + _direction.first,
                                 _body[0].second + _direction.second};

  // Перемещаем голову в зависимости от столкновения с границей
  if (newHead.first < 0) {
    newHead.first = fieldWidth - 1; // Появление с правой стороны
  } else if (newHead.first >= fieldWidth) {
    newHead.first = 0; // Появление с левой стороны
  } else if (newHead.second < 0) {
    newHead.second = fieldHeight - 1; // Появление снизу
  } else if (newHead.second >= fieldHeight) {
    newHead.second = 0; // Появление сверху
  }

  // Добавляем новую голову
  _body.insert(_body.begin(), newHead);

  // Если змейка не съела еду, то удаляем хвост
  if (!_grew) {
    _body.pop_back();
  } else {
    _grew =
        false; // Сбрасываем флаг роста после того как змейка "переваривает" еду
  }
}

void Snake::ChangeDirection(const std::pair<int, int> &newDirection) {
  // Змейка не может разворачиваться на 180 градусов
  if ((_direction.first == 0 && newDirection.first != 0) ||
      (_direction.second == 0 && newDirection.second != 0)) {
    _direction = newDirection;
  }
}
