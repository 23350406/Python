#include "functionsFullProject.h"

Bot::Bot(Bot &&other) noexcept
    : _snake(other._snake) // Просто копируем указатель (не нужно std::move для
                           // указателя)
      ,
      _field(other._field) { // Копируем ссылку на поле
  // Обнуляем указатель у исходного объекта (чтобы избежать двойного удаления)
  other._snake = nullptr;
}

// Оператор присваивания перемещением
Bot &Bot::operator=(Bot &&other) noexcept {
  if (this != &other) {
    _snake = other._snake; // Просто копируем указатель
    _field = other._field; // Копируем ссылку на поле

    // Обнуляем указатель у исходного объекта (чтобы избежать двойного удаления)
    other._snake = nullptr;
  }
  return *this;
}

// Движение бота
void Bot::Move() {
    // Получаем координаты головы змеи
    auto snakeHead = GetSnake().GetBody()[0];
    int snakeHeadX = snakeHead.first;
    int snakeHeadY = snakeHead.second;
    std::pair<int, int> initialDirection = GetSnake().GetDirection();

    // Улучшенный поиск яблока
    int appleX = -1, appleY = -1;
    bool appleFound = false;
    for (int y = 0; y < _field.GetHeight(); ++y) {
        for (int x = 0; x < _field.GetWidth(); ++x) {
            if (_field.GetField()[y][x].GetType() == CellType::FOOD) {
                appleX = x;
                appleY = y;
                appleFound = true;
                break;
            }
        }
        if (appleFound) break;
    }

    if (appleFound) {
        // Рассчитываем направления к яблоку
        std::vector<std::pair<int, int>> priorityDirections;
        if (appleX < snakeHeadX) priorityDirections.push_back({-1, 0}); // Влево
        if (appleX > snakeHeadX) priorityDirections.push_back({1, 0});  // Вправо
        if (appleY < snakeHeadY) priorityDirections.push_back({0, -1}); // Вверх
        if (appleY > snakeHeadY) priorityDirections.push_back({0, 1});  // Вниз

        // Ищем безопасное направление из приоритетных
        for (auto dir : priorityDirections) {
            int newX = snakeHeadX + dir.first;
            int newY = snakeHeadY + dir.second;

            if (newX >= 0 && newX < _field.GetWidth() && newY >= 0 && newY < _field.GetHeight() &&
                !_field.GetField()[newY][newX].GetIsBusy()) {
                  // Змейка не может разворачиваться на 180 градусов
                  if ((initialDirection.first == 0 && dir.first != 0) ||
                  (initialDirection.second == 0 && dir.second != 0)) {
                    GetSnake().ChangeDirection(dir);
                  }
                //break;
            }
            if (newX >= 0 && newX < _field.GetWidth() && newY >= 0 && newY < _field.GetHeight() &&
              _field.GetField()[newY][newX].GetIsBusy()) {
              std::pair<int, int> newDir(dir.second, dir.first);
              // Змейка не может разворачиваться на 180 градусов
              if ((initialDirection.first == 0 && newDir.first != 0) ||
              (initialDirection.second == 0 && newDir.second != 0)) {
                GetSnake().ChangeDirection(newDir);
              }
              //break;
            }
        }
    }

    // Движение змеи
    _snake->MoveSnake(_field.GetWidth(), _field.GetHeight());
}


// Получение позиции головы змейки
std::pair<int, int> Bot::GetHeadPosition() const {
  return _snake->GetBody().front(); // Голова — это первый элемент тела змеи
}

// Ищем ближайшую еду
std::pair<int, int> Bot::FindNearestFood(const std::pair<int, int> &head) {
  std::pair<int, int> bestMove = head;
  int minDistance = std::numeric_limits<int>::max();

  // Ищем ближайшую еду
  for (int y = 0; y < _field.GetHeight(); ++y) {
    for (int x = 0; x < _field.GetWidth(); ++x) {
      if (_field.GetField()[y][x].GetType() == CellType::FOOD) {
        int distance = std::abs(x - head.first) + std::abs(y - head.second);
        if (distance < minDistance) {
          minDistance = distance;
          bestMove = {x, y};
        }
      }
    }
  }

  return bestMove;
}

// Двигаем бота случайным образом, если нет еды
void Bot::MoveRandomly() {
  // Получаем голову змейки
  auto head = _snake->GetBody()[0];

  // Сгенерируем случайное направление
  int randomDirection = rand() % 4;
  switch (randomDirection) {
  case 0:
    _snake->ChangeDirection({1, 0}); // Вправо
    break;
  case 1:
    _snake->ChangeDirection({-1, 0}); // Влево
    break;
  case 2:
    _snake->ChangeDirection({0, 1}); // Вниз
    break;
  case 3:
    _snake->ChangeDirection({0, -1}); // Вверх
    break;
  }

  // Перемещаем змейку
  _snake->MoveSnake(_field.GetWidth(), _field.GetHeight());
}