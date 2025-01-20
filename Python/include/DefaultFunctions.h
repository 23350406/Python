#include "functionsFullProject.h"

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field, Snake &snake) {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Движение змейки по времени (с постоянным интервалом)
        if (clock.getElapsedTime().asSeconds() >= snake.GetMoveSpeed()) {
            snake.MoveSnake(field.GetWidth(), field.GetHeight()); // Автоматическое движение змейки
            clock.restart(); // Перезапускаем таймер
        }

        // Обработка нажатий клавиш для управления направлением змейки
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            snake.ChangeDirection({0, -1}); // вверх
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            snake.ChangeDirection({0, 1}); // вниз
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            snake.ChangeDirection({-1, 0}); // влево
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            snake.ChangeDirection({1, 0}); // вправо
        }

        // Проверка на столкновение с границей (перемещение на противоположную сторону)
        auto head = snake.GetBody()[0];
        if (head.first < 0) {
            // Змейка вылезла за левую границу, появится с правой
            snake.GetBody()[0].first = field.GetWidth() - 1;
        } else if (head.first >= field.GetWidth()) {
            // Змейка вылезла за правую границу, появится с левой
            snake.GetBody()[0].first = 0;
        } else if (head.second < 0) {
            // Змейка вылезла за верхнюю границу, появится снизу
            snake.GetBody()[0].second = field.GetHeight() - 1;
        } else if (head.second >= field.GetHeight()) {
            // Змейка вылезла за нижнюю границу, появится сверху
            snake.GetBody()[0].second = 0;
        }

        // Проверка на столкновение с телом змейки
        for (size_t i = 1; i < snake.GetBody().size(); ++i) {
            if (head == snake.GetBody()[i]) {
                window.clear();   // Очистить экран
                window.display(); // Показать обновленное окно
                return; // Выход из игры при столкновении с собой
            }
        }

        // Проверка на столкновение с препятствием
        if (field.GetField()[head.second][head.first].GetType() == CellType::OBSTACLE) {
            window.clear();   // Очистить экран
            window.display(); // Показать обновленное окно
            // Завершение игры или изменение состояния
            break;
        }

        // Если змейка съела еду
        if (field.GetField()[head.second][head.first].GetType() == CellType::FOOD) {
            snake.Grow(); // Увеличиваем змейку
            // Размещаем еду в новом случайном месте, но проверяем, что в новом месте
            // нет змейки
            do {
                field.PlaceFood();
            } while (field.GetField()[head.second][head.first].GetType() == CellType::SNAKE_BODY ||
                     field.GetField()[head.second][head.first].GetType() == CellType::SNAKE_HEAD);
        }

        // Обновляем карту с текущим состоянием змейки
        field.UpdateMap(snake);

        // Отрисовка
        window.clear();                   // Очистить экран
        DrawMap(window, gameInfo, field); // Отрисовать карту
        window.display(); // Показать обновленное окно
    }
}


int DefineMapSize(string size) {

  if (size == "small") {
    return 20;
  }

  if (size == "medium") {
    return 25;
  }

  if (size == "large") {
    return 30;
  }

  return 25;
}

vector<int> DefineParametersForField(GameInfo &gameInfo) {
  vector<int> result;
  string sizeMap = gameInfo.GetMapSize();

  int digitalMapSize = DefineMapSize(sizeMap);
  result.push_back(digitalMapSize);
  result.push_back(digitalMapSize);

  result.push_back(1);
  result.push_back(gameInfo.GetNumberOfBots());

  return result;
}

vector<int> GenerateRandomValues(int maxSize) {
  vector<int> randomValue;

  // Составим значения для разных штук
  srand(time(0));
  for (int i = 0; i < 7; ++i) {
    int cellForSnake = rand() % (maxSize - 1);
    if (find(randomValue.begin(), randomValue.end(), cellForSnake) ==
        randomValue.end()) {
      randomValue.push_back(cellForSnake);
      continue;
    }
    --i;
  }
  return randomValue;
}