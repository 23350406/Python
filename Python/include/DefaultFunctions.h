#include "functionsFullProject.h"

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              std::vector<Snake> &snakes) {
  sf::Clock playerClock; // Таймер для игрока
  std::vector<sf::Clock> botClocks(snakes.size() -
                                   1); // Таймеры для ботов (если они есть)

  // Инициализация ботов (вне игрового цикла)
  std::vector<Bot> bots;
  for (size_t i = 1; i < snakes.size(); ++i) {
    bots.push_back(Bot(snakes[i], field)); // Инициализация всех ботов
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Движение игрока (первая змейка в векторе)
    if (playerClock.getElapsedTime().asSeconds() >= snakes[0].GetMoveSpeed()) {
      // Обработка нажатий клавиш для управления направлением змейки игрока
      if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetUpKey())) {
        snakes[0].ChangeDirection({0, -1}); // вверх
      } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetDownKey())) {
        snakes[0].ChangeDirection({0, 1}); // вниз
      } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
        snakes[0].ChangeDirection({-1, 0}); // влево
      } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetRightKey())) {
        snakes[0].ChangeDirection({1, 0}); // вправо
      }

      snakes[0].MoveSnake(field.GetWidth(),
                          field.GetHeight()); // Двигаем змейку игрока

      // Проверка на столкновение с границей (стеной)
      auto head = snakes[0].GetBody()[0];
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::OBSTACLE) {
        window.clear();   // Очистить экран
        window.display(); // Показать обновленный экран
        gameInfo.SetCurrentWindowName(
            "Game Over"); // Обновляем экран с результатами
        return;           // Завершаем игровой цикл
      }

      // Проверка на столкновение с телом змейки
      for (size_t i = 1; i < snakes.size(); ++i) {
        for (const auto &bodyPart : snakes[i].GetBody()) {
          if (head == bodyPart) {
            // Столкновение с телом другой змейки
            window.clear(); // Очистить экран
            window.display(); // Показать обновленный экран
            gameInfo.SetCurrentWindowName(
                "Game Over"); // Обновляем экран с результатами
            return;           // Завершаем игровой цикл
          }
        }
      }

      // Если змейка съела еду
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::FOOD) {
        snakes[0].Grow(); // Увеличиваем змейку
        // Размещаем еду в новом случайном месте, но проверяем, что в новом
        // месте нет змейки
        do {
          field.PlaceFood();
        } while (field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_BODY ||
                 field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_HEAD);
      }

      playerClock.restart(); // Перезапускаем таймер игрока
    }

    // Вектор для хранения индексов ботов, которых нужно удалить
    std::vector<size_t> botsToRemove;

    // Движение каждого из ботов
    for (size_t i = 0; i < bots.size();
         ++i) { // Итерируем с начала (индекс i для бота)
      if (botClocks[i].getElapsedTime().asSeconds() >=
          snakes[i + 1].GetMoveSpeed()) {
        Bot &currentBot = bots[i];

        // Перемещение бота
        currentBot.Move(); // Перемещаем бота

        // Получаем позицию головы бота
        auto botHead = currentBot.GetSnake().GetBody()[0];

        // Проверяем, не съел ли бот еду
        if (field.GetField()[botHead.second][botHead.first].GetType() ==
            CellType::FOOD) {
          currentBot.GetSnake().Grow(); // Увеличиваем размер бота

          // Размещаем еду в новом случайном месте
          do {
            field.PlaceFood();
          } while (field.GetField()[botHead.second][botHead.first].GetType() ==
                       CellType::SNAKE_BODY ||
                   field.GetField()[botHead.second][botHead.first].GetType() ==
                       CellType::SNAKE_HEAD);
        }

        // Проверка на столкновение с препятствием
        if (field.GetField()[botHead.second][botHead.first].GetType() ==
            CellType::OBSTACLE) {
          // Столкновение с препятствием - бот "умирает"
          botsToRemove.push_back(i); // Отметим бота для удаления
          botClocks.erase(botClocks.begin() + i); // Удаляем таймер бота
        }

        // Проверка столкновения с телом игрока
        for (const auto &bodyPart : snakes[0].GetBody()) {
          if (botHead == bodyPart) {
            // Столкновение с телом игрока - бот "умирает"
            botsToRemove.push_back(i); // Отметим бота для удаления
            break; // Выход из цикла, так как бот умер
          }
        }

        // Проверка столкновения с другими ботами
        for (size_t j = 0; j < bots.size(); ++j) {
          if (i != j) { // Не проверяем столкновение с самим собой
            auto otherBotHead =
                bots[j].GetSnake().GetBody()[0]; // Получаем голову другого бота

            // Если головы двух ботов совпадают, то происходит столкновение
            if (botHead == otherBotHead) {
              // Столкновение с другим ботом - оба бота "умирают"
              botsToRemove.push_back(i); // Отметим бота для удаления
              botsToRemove.push_back(j); // Отметим второго бота для удаления
            }
          }
        }

        // Перезапускаем таймер бота, если он не столкнулся с препятствием
        botClocks[i].restart();
      }
    }

    // Удаляем ботов, которые должны были "умереть"
for (size_t i = botsToRemove.size(); i-- > 0;) {
  size_t index = botsToRemove[i];
  // Удаляем бот и соответствующую змейку
  bots.erase(bots.begin() + index); // Удаляем бота
  snakes.erase(snakes.begin() + index + 1); // Удаляем змейку (нумерация с 1 для ботов)
}

// Очистим список индексов для удаления
botsToRemove.clear();
    // Обновляем карту с текущим состоянием всех змей
    field.UpdateMap(snakes);

    // Отрисовка
    window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/fon.jpg");

    // Спрайт для фонового изображения
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту

    window.display(); // Показать обновленное окно
  }
}

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &snake) {
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Движение змейки по времени (с постоянным интервалом)
    if (clock.getElapsedTime().asSeconds() >= snake.GetMoveSpeed()) {
      snake.MoveSnake(field.GetWidth(),
                      field.GetHeight()); // Автоматическое движение змейки
      clock.restart(); // Перезапускаем таймер
    }

    // Обработка нажатий клавиш для управления направлением змейки
    if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetUpKey())) {
      snake.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetDownKey())) {
      snake.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
      snake.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetRightKey())) {
      snake.ChangeDirection({1, 0}); // вправо
    }

    // Проверка на столкновение с границей (перемещение на противоположную
    // сторону)
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
    if (field.GetField()[head.second][head.first].GetType() ==
        CellType::OBSTACLE) {
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
      } while (field.GetField()[head.second][head.first].GetType() ==
                   CellType::SNAKE_BODY ||
               field.GetField()[head.second][head.first].GetType() ==
                   CellType::SNAKE_HEAD);
    }

    // Обновляем карту с текущим состоянием змейки
    field.UpdateMap(snake);

    // Отрисовка
    window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/fon.jpg");

    // Спрайт для фонового изображения
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту
    window.display(); // Показать обновленное окно
  }
}

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &snake1, Snake &snake2) {
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Движение змей по времени (с постоянным интервалом)
    if (clock.getElapsedTime().asSeconds() >= snake1.GetMoveSpeed()) {
      snake1.MoveSnake(field.GetWidth(), field.GetHeight());
      snake2.MoveSnake(field.GetWidth(), field.GetHeight());
      clock.restart();
    }

    // Обработка нажатий клавиш для управления первой змейкой
    if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetUpKey())) {
      snake1.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetDownKey())) {
      snake1.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
      snake1.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetRightKey())) {
      snake1.ChangeDirection({1, 0}); // вправо
    }

    // Обработка нажатий клавиш для управления второй змейкой
    if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetUpKey())) {
      snake2.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetDownKey())) {
      snake2.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetLeftKey())) {
      snake2.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetRightKey())) {
      snake2.ChangeDirection({1, 0}); // вправо
    }

    // Проверка на столкновение змей с границами и их перенос на противоположную сторону
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];
      if (head.first < 0) {
        snake.get().GetBody()[0].first = field.GetWidth() - 1;
      } else if (head.first >= field.GetWidth()) {
        snake.get().GetBody()[0].first = 0;
      } else if (head.second < 0) {
        snake.get().GetBody()[0].second = field.GetHeight() - 1;
      } else if (head.second >= field.GetHeight()) {
        snake.get().GetBody()[0].second = 0;
      }
    }

    // Проверка на столкновение с телом каждой змеи
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];
      for (size_t i = 1; i < snake.get().GetBody().size(); ++i) {
        if (head == snake.get().GetBody()[i]) {
          window.clear();
          window.display();
          return; // Выход из игры при столкновении с собой
        }
      }
    }

    if (!snake1.GetBody().empty()) {
  for (auto &segment : snake2.GetBody()) {
    if (snake1.GetBody()[0] == segment) {
      window.clear();
      sf::Texture gameOverTexture;
      gameOverTexture.loadFromFile("../images/gameOver.jpg");
      
      sf::Sprite GOSprite;
      GOSprite.setTexture(gameOverTexture);
      window.draw(GOSprite);

      window.display();
      return;
    }
  }
}

if (!snake2.GetBody().empty()) {
  for (auto &segment : snake1.GetBody()) {
    if (snake2.GetBody()[0] == segment) {
      window.clear();
      sf::Texture gameOverTexture;
      gameOverTexture.loadFromFile("../images/gameOver.jpg");
      
      sf::Sprite GOSprite;
      GOSprite.setTexture(gameOverTexture);
      window.draw(GOSprite);

      window.display();
      return;
    }
  }
}


    // Проверка на столкновение с препятствиями и еду
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];

      // Столкновение с препятствием
      if (field.GetField()[head.second][head.first].GetType() == CellType::OBSTACLE) {
        window.clear();
        window.display();
        return;
      }

      // Змейка съела еду
      if (field.GetField()[head.second][head.first].GetType() == CellType::FOOD) {
        snake.get().Grow();
        do {
          field.PlaceFood();
        } while (field.GetField()[head.second][head.first].GetType() == CellType::SNAKE_BODY ||
                 field.GetField()[head.second][head.first].GetType() == CellType::SNAKE_HEAD);
      }
    }

    // Обновляем карту с текущим состоянием змей
    field.UpdateMap(snake1, snake2);

    // Отрисовка
    window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/fon.jpg");

    // Спрайт для фонового изображения
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту
    window.display(); // Показать обновленное окно
  }
}


int DefineMapSize(string size) {

  if (size == "small") {
    return 15;
  }

  if (size == "medium") {
    return 20;
  }

  if (size == "large") {
    return 25;
  }

  return 20;
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

bool FindApple(Field &field, int &appleX, int &appleY) {
  // Проходим по всем клеткам поля
  for (int y = 0; y < field.GetHeight(); ++y) {
    for (int x = 0; x < field.GetWidth(); ++x) {
      // Проверяем, если в этой клетке есть яблоко (FOOD)
      if (field.GetField()[y][x].GetType() == CellType::FOOD) {
        appleX = x; // Запоминаем координаты яблока
        appleY = y;
        return true; // Яблоко найдено
      }
    }
  }
  return false; // Яблоко не найдено
}

std::string ChoiceSelection(sf::Color color) {
  if (color == sf::Color(255, 0, 0))
  {
    return "../images/Red.png";
  }

  if (color == sf::Color(0, 255, 234))
  {
    return "../images/Aqua.png";
  }

  if (color == sf::Color(233, 148, 0))
  {
    return "../images/Orange.png";
  }

  if (color == sf::Color(255, 246, 0))
  {
    return "../images/Yellow.png";
  }
  if (color == sf::Color(84, 255, 0))
  {
    return "../images/Lime.png";
  }

  if (color == sf::Color(120, 0, 255))
  {
    return "../images/Purple.png";
  }

  if (color == sf::Color(255, 0, 162))
  {
    return "../images/Magenta.png";
  }

  if (color == sf::Color(255, 255, 229))
  {
    return "../images/White.png";
  }
}