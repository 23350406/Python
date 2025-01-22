#include "functionsFullProject.h"

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &playerSnake, std::vector<Snake> &bots) {
  // Таймер для игрока
  sf::Clock playerClock;

  // Таймеры для всех ботов
  std::vector<sf::Clock> botClocks(bots.size());

  // Создание объектов Bot на основе данных о змей ботов
  std::vector<Bot> botsArr;
  for (auto &botSnake : bots) {
    botsArr.emplace_back(
        botSnake, field); // Инициализация бота с помощью его змеи и карты
  }

  while (window.isOpen())
  {
    sf::Event event;

    // Обработка событий
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close(); // Закрытие окна при нажатии на крестик
      }
    }

    // Движение игрока
    if (playerClock.getElapsedTime().asSeconds() >=
        playerSnake.GetMoveSpeed()) {

      // Проверка на нажатие стрелок для изменения направления игрока
      if (sf::Keyboard::isKeyPressed(
              gameInfo.GetFirstPlayerInfo().GetUpKey())) {
        playerSnake.ChangeDirection({0, -1});
      } else if (sf::Keyboard::isKeyPressed(
                     gameInfo.GetFirstPlayerInfo().GetDownKey())) {
        playerSnake.ChangeDirection({0, 1});
      } else if (sf::Keyboard::isKeyPressed(
                     gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
        playerSnake.ChangeDirection({-1, 0});
      } else if (sf::Keyboard::isKeyPressed(
                     gameInfo.GetFirstPlayerInfo().GetRightKey())) {
        playerSnake.ChangeDirection({1, 0});

      }

      // Движение игрока по карте
      playerSnake.MoveSnake(field.GetWidth(), field.GetHeight());

      auto head = playerSnake.GetBody()[0];

      // Проверка на столкновение с препятствием
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::OBSTACLE) {
        window.clear();
        window.display();
        gameInfo.SetCurrentWindowName(
            "Game Over"); // Устанавливаем сообщение об окончании игры
        return;
      }

      // Проверка столкновений между игроком и ботами
      for (const auto &bot : botsArr) {
        for (const auto &bodyPart : bot.GetSnake().GetBody()) {
          if (head == bodyPart) {
            window.clear();
            window.display();
            gameInfo.SetCurrentWindowName("Game Over");
            return;

          }
        }
      }

      // Проверка на столкновение змеи самой с собой
      for (size_t i = 1; i < playerSnake.GetBody().size(); ++i) {
        if (head == playerSnake.GetBody()[i] && playerSnake.GetBody().size() != 3) {
          // Змейка столкнулась с собой
          window.clear();   // Очистка экрана
          window.display(); // Обновление окна
          gameInfo.SetCurrentWindowName(
              "Game Over"); // Сообщение об окончании игры
          return;           // Завершение игрового цикла
        }
      }

      // Проверка на съедание еды
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::FOOD) {
        playerSnake.Grow(); // Увеличение длины змеи
        do {
          field.PlaceFood(); // Расположение новой еды на карте
        } while (field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_BODY ||
                 field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_HEAD);
      }

      playerClock.restart(); // Перезапуск таймера для игрока
    }

    // Движение ботов
    std::vector<size_t> botsToRemove;
    for (size_t i = 0; i < botsArr.size(); ++i) {

      // Если прошло достаточное время с последнего движения бота
      if (botClocks[i].getElapsedTime().asSeconds() >=
          botsArr[i].GetSnake().GetMoveSpeed()) {
        botsArr[i].Move(); // Движение бота

        auto botHead = botsArr[i].GetSnake().GetBody()[0];

        // Проверка на съедание еды
        if (field.GetField()[botHead.second][botHead.first].GetType() ==
            CellType::FOOD) {
          botsArr[i].GetSnake().Grow(); // Увеличение длины змеи бота
          do {
            field.PlaceFood(); // Расположение новой еды на карте
          } while (field.GetField()[botHead.second][botHead.first].GetType() ==
                       CellType::SNAKE_BODY ||
                   field.GetField()[botHead.second][botHead.first].GetType() ==
                       CellType::SNAKE_HEAD);
        }

        // Проверка столкновения с препятствием
        if (field.GetField()[botHead.second][botHead.first].GetType() ==
            CellType::OBSTACLE) {
          botsToRemove.push_back(i); // Добавляем бота в список на удаление
          continue;
        }

        // Проверка столкновения с игроком
        for (const auto &bodyPart : playerSnake.GetBody()) {
          if (botHead == bodyPart) {
            botsToRemove.push_back(
                i); // Удаляем бота если столкновение с игроком
            break;
          }
        }

        // Проверка столкновений между ботами
        for (size_t j = 0; j < botsArr.size(); ++j) {
          if (i != j && botHead == botsArr[j].GetSnake().GetBody()[0]) {
            botsToRemove.push_back(i);
            break;
          }
        }

        // Проверка столкновения с самим собой
        const auto &botBody = botsArr[i].GetSnake().GetBody();
        for (size_t partIdx = 1; partIdx < botBody.size(); ++partIdx) {
          if (botHead == botBody[partIdx]) {
            botsToRemove.push_back(i);
            break;
          }
        }

        botClocks[i].restart(); // Перезапуск таймера для бота
      }
    }

    // Удаление "мертвых" ботов
    for (size_t i = botsToRemove.size(); i-- > 0;) {
      botsArr.erase(botsArr.begin() + botsToRemove[i]);
      botClocks.erase(botClocks.begin() + botsToRemove[i]);
    }

    botsToRemove.clear();

    // Обновление карты с учетом всех змей
    std::vector<Snake> allSnakes;
    allSnakes.push_back(playerSnake); // Добавляем игрока
    for (const auto &bot : botsArr) {
      allSnakes.push_back(bot.GetSnake()); // Добавляем змеи ботов
    }
    field.UpdateMap(allSnakes); // Обновление карты

    // Отрисовка игры
    window.clear(); // Очистка окна от предыдущего кадра

    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/fon.jpg"); // Загрузка фона

    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite); // Отрисовка фона

    DrawMap(window, gameInfo, field); // Отрисовка карты

    window.display(); // Отображение на экране
  }
}

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &snake)
{
  sf::Clock clock;
  int countFlood = 0;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Движение змейки по времени (с постоянным интервалом)
    if (clock.getElapsedTime().asSeconds() >= snake.GetMoveSpeed())
    {
      snake.MoveSnake(field.GetWidth(),
                      field.GetHeight()); // Автоматическое движение змейки
      clock.restart();                    // Перезапускаем таймер
    }

    // Обработка нажатий клавиш для управления направлением змейки
    if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetUpKey()))
    {
      snake.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetDownKey())) {
      snake.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
      snake.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetRightKey())) {

      snake.ChangeDirection({1, 0}); // вправо
    }

    // Проверка на столкновение с границей (перемещение на противоположную
    // сторону)
    auto head = snake.GetBody()[0];
    if (head.first < 0)
    {
      // Змейка вылезла за левую границу, появится с правой
      snake.GetBody()[0].first = field.GetWidth() - 1;
    }
    else if (head.first >= field.GetWidth())
    {
      // Змейка вылезла за правую границу, появится с левой
      snake.GetBody()[0].first = 0;
    }
    else if (head.second < 0)
    {
      // Змейка вылезла за верхнюю границу, появится снизу
      snake.GetBody()[0].second = field.GetHeight() - 1;
    }
    else if (head.second >= field.GetHeight())
    {
      // Змейка вылезла за нижнюю границу, появится сверху
      snake.GetBody()[0].second = 0;
    }

    // Проверка на столкновение с телом змейки
    for (size_t i = 1; i < snake.GetBody().size(); ++i)
    {
      if (head == snake.GetBody()[i])
      {
        window.clear();   // Очистить экран
        window.display(); // Показать обновленное окно
        return;           // Выход из игры при столкновении с собой
      }
    }

    // Проверка на столкновение с препятствием
    if (field.GetField()[head.second][head.first].GetType() ==
        CellType::OBSTACLE)
    {
      window.clear();   // Очистить экран
      window.display(); // Показать обновленное окно
      // Завершение игры или изменение состояния
      break;
    }

    // Если змейка съела еду
    if (field.GetField()[head.second][head.first].GetType() == CellType::FOOD)
    {
      snake.Grow(); // Увеличиваем змейку
      ++countFlood; // Увеличиваем счётчик
      // Размещаем еду в новом случайном месте, но проверяем, что в новом месте
      // нет змейки
      do
      {
        field.PlaceFood();
      } while (field.GetField()[head.second][head.first].GetType() ==
                   CellType::SNAKE_BODY ||
               field.GetField()[head.second][head.first].GetType() ==
                   CellType::SNAKE_HEAD);
    }

    // Обновляем карту с текущим состоянием змейки
    field.UpdateMap(snake);

    // Отрисовка
    // window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/menu2.png");

    //----------------------------------------------------------------------
    sf::Font font;
    font.loadFromFile("../fonts/Consolas.ttf");

    sf::Text p1;
    p1.setFont(font);
    p1.setCharacterSize(24);           // Размер шрифта
    p1.setFillColor(sf::Color::White); // Цвет текста
    p1.setPosition(940, 80); // Позиция текста на экране
    p1.setString(gameInfo.GetFirstPlayerInfo().GetName());
    if (gameInfo.GetIsSolo()) {
      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150);          // Позиция текста на экране
      p2.setString("None");
      window.draw(p2); // Рисуем текст
      
    } else {
      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150);          // Позиция текста на экране
      p2.setString(gameInfo.GetSecondPlayerInfo().GetName());
      window.draw(p2); // Рисуем текст
    }

    sf::Text Round;
    std::string roundInfo = "Rounds: ";
    Round.setFont(font);
    Round.setCharacterSize(24);           // Размер шрифта
    Round.setFillColor(sf::Color::White); // Цвет текста
    Round.setPosition(940, 220);          // Позиция текста на экране
    Round.setString(roundInfo + std::to_string(gameInfo.GetNumberOfRounds()));

    sf::Text Bots;
    std::string botsInfo = "Round: ";
      Bots.setFont(font);
      Bots.setCharacterSize(24); // Размер шрифта
      Bots.setFillColor(sf::Color::White); // Цвет текста
      Bots.setPosition(940, 290); // Позиция текста на экране
      Bots.setString(botsInfo + std::to_string(gameInfo.GetNumberOfBots()));

    sf::Text Score;
    std::string scoreInfo = "Score: ";
    Score.setFont(font);
    Score.setCharacterSize(24);           // Размер шрифта
    Score.setFillColor(sf::Color::White); // Цвет текста
    Score.setPosition(940, 360); // Позиция текста на экране
    Score.setString(scoreInfo + std::to_string(countFlood));

    window.draw(p1);
    window.draw(Round); // Рисуем текст
    window.draw(Bots);  // Рисуем текст
    window.draw(Score); // Рисуем текст
    window.display();
    //----------------------------------------------------------------------
    // Спрайт для фонового изображения
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту
  }
}

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &snake1, Snake &snake2)
{
  sf::Clock clock;
  int countFlood1 = 0;
  int countFlood2 = 0;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Движение змей по времени (с постоянным интервалом)
    if (clock.getElapsedTime().asSeconds() >= snake1.GetMoveSpeed())
    {
      snake1.MoveSnake(field.GetWidth(), field.GetHeight());
      snake2.MoveSnake(field.GetWidth(), field.GetHeight());
      clock.restart();
    }

    // Обработка нажатий клавиш для управления первой змейкой
    if (sf::Keyboard::isKeyPressed(gameInfo.GetFirstPlayerInfo().GetUpKey()))
    {
      snake1.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetDownKey())) {
      snake1.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
      snake1.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetRightKey())) 
      snake1.ChangeDirection({1, 0}); // вправо
    }

    // Обработка нажатий клавиш для управления второй змейкой
    if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetUpKey()))
    {
      snake2.ChangeDirection({0, -1}); // вверх
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetSecondPlayerInfo().GetDownKey())) {
      snake2.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetSecondPlayerInfo().GetLeftKey())) {
      snake2.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetSecondPlayerInfo().GetRightKey())) {
      snake2.ChangeDirection({1, 0}); // вправо
    }

    // Проверка на столкновение змей с границами и их перенос на противоположную
    // сторону
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];
      if (head.first < 0)
      {
        snake.get().GetBody()[0].first = field.GetWidth() - 1;
      }
      else if (head.first >= field.GetWidth())
      {
        snake.get().GetBody()[0].first = 0;
      }
      else if (head.second < 0)
      {
        snake.get().GetBody()[0].second = field.GetHeight() - 1;
      }
      else if (head.second >= field.GetHeight())
      {
        snake.get().GetBody()[0].second = 0;
      }
    }

    // Проверка на столкновение змейки с собственным телом
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];
      for (size_t i = 1; i < snake.get().GetBody().size(); ++i) {
        if (head == snake.get().GetBody()[i] &&
            snake.get().GetBody().size() != 3) {
          // Змейка столкнулась с собой
          window.clear(sf::Color::Black); // Закрашиваем экран в черный
          window.display();               // Показываем экран
          return;                         // Завершаем функцию
        }
      }
    }

    // Проверка на столкновение с телом каждой змеи
    if (!snake1.GetBody().empty()) {
      for (auto &segment : snake2.GetBody()) {
        if (snake1.GetBody()[0] == segment) {
          window.clear(sf::Color::Black);
          
          sf::Texture gameOverTexture;
          gameOverTexture.loadFromFile("../images/restart.png");

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
          window.clear(sf::Color::Black);

          window.clear();
          sf::Texture gameOverTexture;
          gameOverTexture.loadFromFile("../images/restart.png");

          sf::Sprite GOSprite;
          GOSprite.setTexture(gameOverTexture);
          window.draw(GOSprite);

          window.display();
          return;
        }
      }
    }

    // Проверка на столкновение с препятствиями и еду
    for (auto &snake : {std::ref(snake1), std::ref(snake2)})
    {
      auto head = snake.get().GetBody()[0];

      // Столкновение с препятствием
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::OBSTACLE) {
        window.clear(sf::Color::Black); // Закрашиваем экран в черный цвет
        window.display(); // Обновляем окно, чтобы показать черный экран
        return; // Завершаем функцию, чтобы остановить игровой цикл
      }

      // Змейка съела еду
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::FOOD) {
        ++countFlood;
        
        snake.get().Grow();
        do
        {
          field.PlaceFood();
        } while (field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_BODY ||
                 field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_HEAD);
      }
    }

    // Обновляем карту с текущим состоянием змей
    field.UpdateMap(snake1, snake2);

    // Отрисовка
    // window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    // fonTexture.loadFromFile("../images/fon.jpg");

    fonTexture.loadFromFile("../images/menu2.png");
    //----------------------------------------------------------------------
    sf::Font font;
    font.loadFromFile("../fonts/Consolas.ttf");

    sf::Text p1;
    p1.setFont(font);
    p1.setCharacterSize(24);           // Размер шрифта
    p1.setFillColor(sf::Color::White); // Цвет текста
    p1.setPosition(940, 80); // Позиция текста на экране
    p1.setString(gameInfo.GetFirstPlayerInfo().GetName());
    if (gameInfo.GetIsSolo()) {

      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150);          // Позиция текста на экране
      p2.setString("None");
      window.draw(p2); // Рисуем текст

    } else {
      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150);          // Позиция текста на экране
      p2.setString(gameInfo.GetSecondPlayerInfo().GetName());
      window.draw(p2); // Рисуем текст
    }

    sf::Text Round;
    std::string roundInfo = "Round: ";
    Round.setFont(font);
    Round.setCharacterSize(24);           // Размер шрифта
    Round.setFillColor(sf::Color::White); // Цвет текста

    Round.setPosition(940, 220);          // Позиция текста на экране
    Round.setString(roundInfo + std::to_string(gameInfo.GetNumberOfRounds()));

    sf::Text Score1;
    std::string score1Info = "Score 1: ";
    Score1.setFont(font);
    Score1.setCharacterSize(24);           // Размер шрифта
    Score1.setFillColor(sf::Color::White); // Цвет текста
    Score1.setPosition(940, 290);          // Позиция текста на экране
    Score1.setString(score1Info + std::to_string(gameInfo.GetNumberOfBots()));

    sf::Text Score2;
    std::string score2Info = "Score 2: ";
    Score2.setFont(font);
    Score2.setCharacterSize(24);           // Размер шрифта
    Score2.setFillColor(sf::Color::White); // Цвет текста
    Score2.setPosition(940, 360);          // Позиция текста на экране
    Score2.setString(score2Info + std::to_string(countFlood));

    window.draw(p1);
    window.draw(Round); // Рисуем текст
    window.draw(Score1);  // Рисуем текст
    window.draw(Score2); // Рисуем текст
    window.display();

    //----------------------------------------------------------------------
    // Спрайт для фонового изображения
    window.display();
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту
  }
}

int DefineMapSize(string size)
{

  if (size == "small")
  {
    return 15;
  }

  if (size == "medium")
  {
    return 20;
  }

  if (size == "large")
  {
    return 25;
  }

  return 20;
}

vector<int> DefineParametersForField(GameInfo &gameInfo)
{
  vector<int> result;
  string sizeMap = gameInfo.GetMapSize();

  int digitalMapSize = DefineMapSize(sizeMap);
  result.push_back(digitalMapSize);
  result.push_back(digitalMapSize);

  result.push_back(1);
  result.push_back(gameInfo.GetNumberOfBots());

  return result;
}

vector<int> GenerateRandomValues(int maxSize)
{
  vector<int> randomValue;

  // Составим значения для разных штук
  srand(time(0));
  for (int i = 0; i < 7; ++i)
  {
    int cellForSnake = rand() % (maxSize - 1);
    if (find(randomValue.begin(), randomValue.end(), cellForSnake) ==
        randomValue.end())
    {
      randomValue.push_back(cellForSnake);
      continue;
    }
    --i;
  }
  return randomValue;
}

bool FindApple(Field &field, int &appleX, int &appleY)
{
  // Проходим по всем клеткам поля
  for (int y = 0; y < field.GetHeight(); ++y)
  {
    for (int x = 0; x < field.GetWidth(); ++x)
    {
      // Проверяем, если в этой клетке есть яблоко (FOOD)
      if (field.GetField()[y][x].GetType() == CellType::FOOD)
      {
        appleX = x; // Запоминаем координаты яблока
        appleY = y;
        return true; // Яблоко найдено
      }
    }
  }
  return false; // Яблоко не найдено
}

std::string ChoiceSelection(sf::Color color) {
  if (color == sf::Color(255, 0, 0)) {

    return "../images/Red.png";
  }

  if (color == sf::Color(0, 255, 234)) {
    return "../images/Aqua.png";
  }

  if (color == sf::Color(233, 148, 0)) {
    return "../images/Orange.png";
  }

  if (color == sf::Color(255, 246, 0)) {
    return "../images/Yellow.png";
  }
  if (color == sf::Color(84, 255, 0)) {
    return "../images/Lime.png";
  }

  if (color == sf::Color(120, 0, 255)) {
    return "../images/Purple.png";
  }

  if (color == sf::Color(255, 0, 162)) {
    return "../images/Magenta.png";
  }

  if (color == sf::Color(255, 255, 229)) {
    return "../images/White.png";
  }
}