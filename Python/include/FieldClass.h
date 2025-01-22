#include "functionsFullProject.h"

Field::Field(int height, int width) : _height(height), _width(width) {
  _field.resize(_height, std::vector<Cell>(_width));

  // Инициализация карты
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      _field[y][x] = Cell(); // Все ячейки по умолчанию пустые
    }
  }

  PlaceFood();
  int countObstacles = 3;
  switch(height) {
    case 15: 
      countObstacles = 8;
      break;
    case 20: 
      countObstacles = 13;
      break;
    case 25: 
      countObstacles = 20;
      break;
  }
  PlaceObstacles(countObstacles);
}

void Field::PlaceObstacles(int numberOfObstacles) {
  std::srand(std::time(nullptr));
  int obstacleX, obstacleY;

  for (int i = 0; i < numberOfObstacles; ++i) {
    do {
      obstacleX = rand() % _width;
      obstacleY = rand() % _height;
    } while (_field[obstacleY][obstacleX].GetType() !=
             CellType::EMPTY); // Проверяем, что ячейка пуста

    // Размещение препятствия
    _field[obstacleY][obstacleX].SetType(CellType::OBSTACLE);
    _field[obstacleY][obstacleX].SetIsBusy(true);
  }
}


void Field::PlaceFood() {
  std::srand(std::time(nullptr));
  int foodX, foodY;

  do {
    foodX = rand() % _width;
    foodY = rand() % _height;
  } while (_field[foodY][foodX].GetType() !=
           CellType::EMPTY); // Проверяем, что ячейка пуста (т.е. тип - EMPTY)

  // Размещение еды на поле
  SetFood(foodX, foodY);
}

void Field::UpdateMap(const std::vector<Snake> &snakes) {
    // Сначала очищаем карту, но не трогаем еду и препятствия
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            // Если клетка не пустая и не еда, сбрасываем её
            if (_field[y][x].GetType() != CellType::FOOD &&
                _field[y][x].GetType() != CellType::OBSTACLE) {
                _field[y][x].SetType(CellType::EMPTY);
                _field[y][x].SetIsBusy(false);
            }
        }
    }

    // Обновляем карту для каждой змейки
    for (const auto &snake : snakes) {
        if (!snake.GetBody().empty()) {
            if (&snake == &snakes.front()) {
                // Если змея первая в массиве
                _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetType(CellType::SNAKE_HEAD_1);  // Голова первой змеи
                _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetIsBusy(true);
                for (size_t i = 1; i < snake.GetBody().size() - 1; ++i) {
                    _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetType(CellType::SNAKE_BODY_1);
                    _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetIsBusy(true);
                }
                _field[snake.GetBody().back().second][snake.GetBody().back().first].SetType(CellType::SNAKE_TAIL_1);  // Хвост первой змеи
                _field[snake.GetBody().back().second][snake.GetBody().back().first].SetIsBusy(true);
            } else {
                _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetType(CellType::SNAKE_HEAD_2);  // Голова остальных змей
                _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetIsBusy(true);
                for (size_t i = 1; i < snake.GetBody().size() - 1; ++i) {
                    _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetType(CellType::SNAKE_BODY_2);
                    _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetIsBusy(true);
                }
                _field[snake.GetBody().back().second][snake.GetBody().back().first].SetType(CellType::SNAKE_TAIL_2);  // Хвост остальных змей
                _field[snake.GetBody().back().second][snake.GetBody().back().first].SetIsBusy(true);
            }
        }
    }
}



void Field::UpdateMap(const Snake &snake) {
  // Сначала очищаем карту, но не трогаем еду и препятствия
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      // Если клетка не пустая и не еда, сбрасываем её
      if (_field[y][x].GetType() != CellType::FOOD &&
          _field[y][x].GetType() != CellType::OBSTACLE) {
        _field[y][x].SetType(CellType::EMPTY);
        _field[y][x].SetIsBusy(false);
      }
    }
  }

  // Обновляем карту в соответствии с текущими координатами змейки
  if (!snake.GetBody().empty()) {
    // Голова змейки
    _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetType(
        CellType::SNAKE_HEAD_1);
        _field[snake.GetBody()[0].second][snake.GetBody()[0].first].SetIsBusy(
        true);

    // Тело змейки
    for (size_t i = 1; i < snake.GetBody().size() - 1; ++i) {
      _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetType(
          CellType::SNAKE_BODY_1);
          _field[snake.GetBody()[i].second][snake.GetBody()[i].first].SetIsBusy(
          true);
    }

    // Хвост змейки
    if (snake.GetBody().size() > 1) {
      _field[snake.GetBody().back().second][snake.GetBody().back().first]
          .SetType(CellType::SNAKE_TAIL_1);
          _field[snake.GetBody().back().second][snake.GetBody().back().first]
          .SetIsBusy(true);
    }
  }
}

void Field::UpdateMap(const Snake &snake1, const Snake &snake2) {
  // Очищаем карту, оставляя еду и препятствия
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      if (_field[y][x].GetType() != CellType::FOOD &&
          _field[y][x].GetType() != CellType::OBSTACLE) {
        _field[y][x].SetType(CellType::EMPTY);
        _field[y][x].SetIsBusy(false);
      }
    }
  }

  // Обновляем карту для первой змеи
  if (!snake1.GetBody().empty()) {
    _field[snake1.GetBody()[0].second][snake1.GetBody()[0].first].SetType(CellType::SNAKE_HEAD_1);
    _field[snake1.GetBody()[0].second][snake1.GetBody()[0].first].SetIsBusy(true);
    for (size_t i = 1; i < snake1.GetBody().size() - 1; ++i) {
      _field[snake1.GetBody()[i].second][snake1.GetBody()[i].first].SetType(CellType::SNAKE_BODY_1);
      _field[snake1.GetBody()[i].second][snake1.GetBody()[i].first].SetIsBusy(true);
    }
    _field[snake1.GetBody().back().second][snake1.GetBody().back().first].SetType(CellType::SNAKE_TAIL_1);
    _field[snake1.GetBody().back().second][snake1.GetBody().back().first].SetIsBusy(true);
  }

  // Обновляем карту для второй змеи
  if (!snake2.GetBody().empty()) {
    _field[snake2.GetBody()[0].second][snake2.GetBody()[0].first].SetType(CellType::SNAKE_HEAD_2);
    _field[snake2.GetBody()[0].second][snake2.GetBody()[0].first].SetIsBusy(true);
    for (size_t i = 1; i < snake2.GetBody().size() - 1; ++i) {
      _field[snake2.GetBody()[i].second][snake2.GetBody()[i].first].SetType(CellType::SNAKE_BODY_2);
      _field[snake2.GetBody()[i].second][snake2.GetBody()[i].first].SetIsBusy(true);
    }
    _field[snake2.GetBody().back().second][snake2.GetBody().back().first].SetType(CellType::SNAKE_TAIL_2);
    _field[snake2.GetBody().back().second][snake2.GetBody().back().first].SetIsBusy(true);
  }
}


