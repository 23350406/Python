#include "functionsFullProject.h"

Snake::Snake(int startX, int startY) {
  _body.emplace_back(startX, startY);  // Инициализация головы змеи
  _direction = {0, 0};  // Начальное направление движения
  _grew = false;  // Змейка ещё не выросла
}


std::vector<std::pair<int, int>> Snake::GetBody() const { return _body; }

void Snake::Grow() {
  // Добавляем новую часть в хвост, которая будет иметь те же координаты, что и
  // текущий хвост
  std::pair<int, int> newTail =
      _body.back(); // Координаты последней части змейки
  _body.push_back(newTail); // Добавляем эту координату как новый сегмент
}

void Snake::MoveSnake(int fieldWidth, int fieldHeight) {
  // Вычисляем новые координаты головы
  std::pair<int, int> newHead = {_body[0].first + _direction.first,
                                 _body[0].second + _direction.second};

  // Перемещаем голову в зависимости от выхода за границы
  if (newHead.first < 0) {
    newHead.first = fieldWidth - 1;
  } else if (newHead.first >= fieldWidth) {
    newHead.first = 0;
  } else if (newHead.second < 0) {
    newHead.second = fieldHeight - 1;
  } else if (newHead.second >= fieldHeight) {
    newHead.second = 0;
  }

  // Добавляем новую голову
  _body.insert(_body.begin(), newHead);
  _body.pop_back(); // Удаляем хвост
}



void Snake::MoveBot(int fieldWidth, int fieldHeight) {
    // Простая логика для бота: случайное направление
    // Сначала определяем случайное направление
    static sf::Clock moveClock;
    if (moveClock.getElapsedTime().asSeconds() > 0.5f) { // Бот меняет направление раз в 0.5 секунд
        int direction = rand() % 4; // Случайное направление (0-3)
        switch (direction) {
            case 0: // Вверх
                ChangeDirection({0, -1});
                break;
            case 1: // Вниз
                ChangeDirection({0, 1});
                break;
            case 2: // Влево
                ChangeDirection({-1, 0});
                break;
            case 3: // Вправо
                ChangeDirection({1, 0});
                break;
        }
        moveClock.restart(); // Перезапускаем таймер
    }
    
    // Теперь выполняем движение змейки (то же, что и для игрока)
    std::pair<int, int> newHead = {_body[0].first + _direction.first, _body[0].second + _direction.second};
    
    // Обработка столкновений с границами
    if (newHead.first < 0) newHead.first = fieldWidth - 1;
    if (newHead.first >= fieldWidth) newHead.first = 0;
    if (newHead.second < 0) newHead.second = fieldHeight - 1;
    if (newHead.second >= fieldHeight) newHead.second = 0;

    // Добавляем новую голову
    _body.insert(_body.begin(), newHead);

    _body.pop_back();
}


void Snake::ChangeDirection(const std::pair<int, int> &newDirection) {
  // Змейка не может разворачиваться на 180 градусов
  if ((_direction.first == 0 && newDirection.first != 0) ||
      (_direction.second == 0 && newDirection.second != 0)) {
    _direction = newDirection;
  }
}
