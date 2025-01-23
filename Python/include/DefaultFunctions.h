#include "functionsFullProject.h"
#include <iostream>

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &playerSnake, std::vector<Snake> &bots) {
  // Таймер для игрока
  sf::Clock playerClock;
  int countFlood = 0;
  sf::Texture gameOverTexture;
  gameOverTexture.loadFromFile("../images/restart.png");

  sf::Sprite GOSprite;
  GOSprite.setTexture(gameOverTexture);

  // Таймеры для всех ботов
  std::vector<sf::Clock> botClocks(bots.size());

  // Создание объектов Bot на основе данных о змей ботов
  std::vector<Bot> botsArr;
  for (auto &botSnake : bots) {
    botsArr.emplace_back(
        botSnake, field); // Инициализация бота с помощью его змеи и карты
  }

  while (window.isOpen()) {
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

        if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
          sf::Texture endRounds;
          sf::Sprite endRoundsSprite;

          endRounds.loadFromFile("../images/FonEndRound.png");
          endRoundsSprite.setTexture(endRounds);

          sf::Font font;
          font.loadFromFile("../fonts/Consolas.ttf");

          sf::Text textLose;
          textLose.setFont(font);
          textLose.setCharacterSize(95);           // Размер шрифта
          textLose.setFillColor(sf::Color::White); // Цвет текста
          textLose.setPosition(140, 250); // Позиция текста на экране
          textLose.setString(gameInfo.GetFirstPlayerInfo().GetName() +
                             " LOOOOSER");

          window.draw(endRoundsSprite);
          window.draw(textLose);
          window.display();

          // Задержка на 3 секунды
          sf::sleep(sf::seconds(3));
        } else {
          window.draw(GOSprite);
          window.display();
          gameInfo.SetCurrentWindowName("GameOver");
          return;
        }

        gameInfo.SetCurrentWindowName(
            "GameOver"); // Устанавливаем сообщение об окончании игры
        return;
      }

      // Проверка столкновений между игроком и ботами
      for (const auto &bot : botsArr) {
        for (const auto &bodyPart : bot.GetSnake().GetBody()) {
          if (head == bodyPart) {
            window.clear();

            if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
              sf::Texture endRounds;
              sf::Sprite endRoundsSprite;

              endRounds.loadFromFile("../images/FonEndRound.png");
              endRoundsSprite.setTexture(endRounds);

              sf::Font font;
              font.loadFromFile("../fonts/Consolas.ttf");

              sf::Text textLose;
              textLose.setFont(font);
              textLose.setCharacterSize(95); // Размер шрифта
              textLose.setFillColor(sf::Color::White); // Цвет текста
              textLose.setPosition(140, 250); // Позиция текста на экране
              textLose.setString(gameInfo.GetFirstPlayerInfo().GetName() +
                                 " LOOOOSER");

              window.draw(endRoundsSprite);
              window.draw(textLose);
              window.display();

              // Задержка на 3 секунды
              sf::sleep(sf::seconds(3));
            }

            else {
              window.draw(GOSprite);
              window.display();
              gameInfo.SetCurrentWindowName("GameOver");
              return;
            }

            gameInfo.SetCurrentWindowName("GameOver");
            return;
          }
        }
      }

      // Проверка на столкновение змеи самой с собой
      for (size_t i = 1; i < playerSnake.GetBody().size(); ++i) {
        if (head == playerSnake.GetBody()[i] &&
            playerSnake.GetBody().size() != 3) {
          // Змейка столкнулась с собой
          window.clear();

          if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
            sf::Texture endRounds;
            sf::Sprite endRoundsSprite;

            endRounds.loadFromFile("../images/FonEndRound.png");
            endRoundsSprite.setTexture(endRounds);

            sf::Font font;
            font.loadFromFile("../fonts/Consolas.ttf");

            sf::Text textLose;
            textLose.setFont(font);
            textLose.setCharacterSize(95); // Размер шрифта
            textLose.setFillColor(sf::Color::White); // Цвет текста
            textLose.setPosition(140, 250); // Позиция текста на экране
            textLose.setString(gameInfo.GetFirstPlayerInfo().GetName() +
                               " LOOOOSER");

            window.draw(endRoundsSprite);
            window.draw(textLose);
            window.display();

            // Задержка на 3 секунды
            sf::sleep(sf::seconds(3));
          }

          else {
            window.draw(GOSprite);
            window.display();
            gameInfo.SetCurrentWindowName("GameOver");
            return;
          }

          gameInfo.SetCurrentWindowName(
              "GameOver"); // Сообщение об окончании игры
          return;          // Завершение игрового цикла
        }
      }

      // Проверка на съедание еды
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::FOOD) {
        ++countFlood;
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

    // Если все боты умерли, то раунд окончен
    if (botsArr.empty() && gameInfo.GetNumberOfBots() != 0) {
      window.clear();
      if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
        sf::Texture endRounds;
        sf::Sprite endRoundsSprite;

        endRounds.loadFromFile("../images/FonEndRound.png");
        endRoundsSprite.setTexture(endRounds);

        sf::Font font;
        font.loadFromFile("../fonts/Consolas.ttf");

        sf::Text textLose;
        textLose.setFont(font);
        textLose.setCharacterSize(95);           // Размер шрифта
        textLose.setFillColor(sf::Color::White); // Цвет текста
        textLose.setPosition(140, 250); // Позиция текста на экране
        textLose.setString("BOTS LOOOOSER");

        window.draw(endRoundsSprite);
        window.draw(textLose);
        window.display();

        // Задержка на 3 секунды
        sf::sleep(sf::seconds(3));
      }

      window.display();
      return;
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

    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/menu2.png");
    //----------------------------------------------------------------------
    sf::Image image = fonTexture.copyToImage();

    // Изменяем цвет определенных пикселей
    for (unsigned int x = 879; x < 920; ++x) {
      for (unsigned int y = 68; y < 109; ++y) {
        image.setPixel(x, y,
                       gameInfo.GetFirstPlayerInfo()
                           .GetColor()); // Устанавливаем красный цвет
      }
    }

    for (unsigned int x = 879; x < 920; ++x) {
      for (unsigned int y = 134; y < 175; ++y) {
        image.setPixel(x, y,
                       gameInfo.GetSecondPlayerInfo()
                           .GetColor()); // Устанавливаем красный цвет
      }
    }

    fonTexture.loadFromImage(image);

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
      p2.setPosition(940, 150); // Позиция текста на экране
      p2.setString("Bot");
      window.draw(p2); // Рисуем текст

    } else {
      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150); // Позиция текста на экране
      p2.setString(gameInfo.GetSecondPlayerInfo().GetName());
      window.draw(p2); // Рисуем текст
    }

    sf::Text Round;
    std::string roundInfo = "Round: ";
    Round.setFont(font);
    Round.setCharacterSize(24);           // Размер шрифта
    Round.setFillColor(sf::Color::White); // Цвет текста
    Round.setPosition(940, 220); // Позиция текста на экране
    Round.setString(roundInfo + std::to_string(gameInfo.GetCurrentRound()));

    sf::Text bots;
    std::string score1Info = "Bots: ";
    bots.setFont(font);
    bots.setCharacterSize(24);           // Размер шрифта
    bots.setFillColor(sf::Color::White); // Цвет текста
    bots.setPosition(940, 290); // Позиция текста на экране
    bots.setString(score1Info + std::to_string(botsArr.size()));

    sf::Text Score;
    std::string score2Info = "Score: ";
    Score.setFont(font);
    Score.setCharacterSize(24);           // Размер шрифта
    Score.setFillColor(sf::Color::White); // Цвет текста
    Score.setPosition(940, 360); // Позиция текста на экране
    Score.setString(score2Info + std::to_string(countFlood));

    window.draw(p1);
    window.draw(Round); // Рисуем текст
    window.draw(Score); // Рисуем текст
    window.draw(bots);  // Рисуем текст
    window.display();

    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовка карты
  }
}

void GameLoop(sf::RenderWindow &window, GameInfo &gameInfo, Field &field,
              Snake &snake1, Snake &snake2) {
  sf::Clock clock;
  int countFlood1 = 0;
  int countFlood2 = 0;
  sf::Texture gameOverTexture;
  gameOverTexture.loadFromFile("../images/restart.png");

  sf::Sprite GOSprite;
  GOSprite.setTexture(gameOverTexture);

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
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetDownKey())) {
      snake1.ChangeDirection({0, 1}); // вниз
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetLeftKey())) {
      snake1.ChangeDirection({-1, 0}); // влево
    } else if (sf::Keyboard::isKeyPressed(
                   gameInfo.GetFirstPlayerInfo().GetRightKey())) {
      snake1.ChangeDirection({1, 0}); // вправо
    }

    // Обработка нажатий клавиш для управления второй змейкой
    if (sf::Keyboard::isKeyPressed(gameInfo.GetSecondPlayerInfo().GetUpKey())) {
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

    // Проверка на столкновение змейки с собственным телом
    bool flag = false;
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {

      auto head = snake.get().GetBody()[0];
      for (size_t i = 1; i < snake.get().GetBody().size(); ++i) {
        if (head == snake.get().GetBody()[i] &&
            snake.get().GetBody().size() != 3) {
          // Змейка столкнулась с собой
          window.clear();

          if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
            sf::Texture endRounds;
            sf::Sprite endRoundsSprite;

            endRounds.loadFromFile("../images/FonEndRound.png");
            endRoundsSprite.setTexture(endRounds);

            sf::Font font;
            font.loadFromFile("../fonts/Consolas.ttf");

            sf::Text textLose;
            textLose.setFont(font);
            textLose.setCharacterSize(95); // Размер шрифта
            textLose.setFillColor(sf::Color::White); // Цвет текста
            textLose.setPosition(140, 250); // Позиция текста на экране
            textLose.setString(gameInfo.GetFirstPlayerInfo().GetName() +
                               " LOOOOSER");
            if (flag) {
              textLose.setString(gameInfo.GetSecondPlayerInfo().GetName() +
                                 " LOOOOSER");
              flag = false;
            }

            window.draw(endRoundsSprite);
            window.draw(textLose);
            window.display();

            // Задержка на 3 секунды
            sf::sleep(sf::seconds(3));
          } else {
            window.draw(GOSprite);
            window.display();
            gameInfo.SetCurrentWindowName("GameOver");
            return;
          }

          gameInfo.SetCurrentWindowName("GameOver");
          return; // Завершаем функцию
        }
      }
      flag = true;
    }

    // Проверка на столкновение с телом каждой змеи
    if (!snake1.GetBody().empty()) {
      for (auto &segment : snake2.GetBody()) {
        if (snake1.GetBody()[0] == segment) {
          window.clear();

          if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
            sf::Texture endRounds;
            sf::Sprite endRoundsSprite;

            endRounds.loadFromFile("../images/FonEndRound.png");
            endRoundsSprite.setTexture(endRounds);

            sf::Font font;
            font.loadFromFile("../fonts/Consolas.ttf");

            sf::Text textLose;
            textLose.setFont(font);
            textLose.setCharacterSize(95); // Размер шрифта
            textLose.setFillColor(sf::Color::White); // Цвет текста
            textLose.setPosition(140, 250); // Позиция текста на экране
            textLose.setString(gameInfo.GetSecondPlayerInfo().GetName() +
                               " LOOOOSER");

            window.draw(endRoundsSprite);
            window.draw(textLose);
            window.display();

            // Задержка на 3 секунды
            sf::sleep(sf::seconds(3));
          } else {
            window.draw(GOSprite);
            window.display();
            gameInfo.SetCurrentWindowName("GameOver");
            return;
          }

          gameInfo.SetCurrentWindowName("GameOver");
          return;
        }
      }
    }

    if (!snake2.GetBody().empty()) {
      for (auto &segment : snake1.GetBody()) {
        if (snake2.GetBody()[0] == segment) {
          window.clear();

          if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
            sf::Texture endRounds;
            sf::Sprite endRoundsSprite;

            endRounds.loadFromFile("../images/FonEndRound.png");
            endRoundsSprite.setTexture(endRounds);

            sf::Font font;
            font.loadFromFile("../fonts/Consolas.ttf");

            sf::Text textLose;
            textLose.setFont(font);
            textLose.setCharacterSize(95); // Размер шрифта
            textLose.setFillColor(sf::Color::White); // Цвет текста
            textLose.setPosition(140, 250); // Позиция текста на экране
            textLose.setString(gameInfo.GetSecondPlayerInfo().GetName() +
                               " LOOOOSER");

            window.draw(endRoundsSprite);
            window.draw(textLose);
            window.display();

            // Задержка на 3 секунды
            sf::sleep(sf::seconds(3));
          } else {
            window.draw(GOSprite);
            window.display();
            gameInfo.SetCurrentWindowName("GameOver");
            return;
          }

          gameInfo.SetCurrentWindowName("GameOver");
          return;
        }
      }
    }

    bool flag2 = false;
    bool flag3 = true;
    // Проверка на столкновение с препятствиями и еду
    for (auto &snake : {std::ref(snake1), std::ref(snake2)}) {
      auto head = snake.get().GetBody()[0];

      // Столкновение с препятствием
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::OBSTACLE) {
        window.clear();

        if (gameInfo.GetCurrentRound() != gameInfo.GetNumberOfRounds()) {
          sf::Texture endRounds;
          sf::Sprite endRoundsSprite;

          endRounds.loadFromFile("../images/FonEndRound.png");
          endRoundsSprite.setTexture(endRounds);

          sf::Font font;
          font.loadFromFile("../fonts/Consolas.ttf");

          sf::Text textLose;
          textLose.setFont(font);
          textLose.setCharacterSize(95);           // Размер шрифта
          textLose.setFillColor(sf::Color::White); // Цвет текста
          textLose.setPosition(140, 250); // Позиция текста на экране
          textLose.setString(gameInfo.GetFirstPlayerInfo().GetName() +
                             " LOOOOSER");
          if (flag2) {
            textLose.setString(gameInfo.GetSecondPlayerInfo().GetName() +
                               " LOOOOSER");
            flag2 = false;
          }

          window.draw(endRoundsSprite);
          window.draw(textLose);
          window.display();

          // Задержка на 3 секунды
          sf::sleep(sf::seconds(3));
        } else {
          window.draw(GOSprite);
          window.display();
          gameInfo.SetCurrentWindowName("GameOver");
          return;
        }

        gameInfo.SetCurrentWindowName("GameOver");
        return; // Завершаем функцию, чтобы остановить игровой цикл
      }
      flag2 = true;

      
      // Змейка съела еду
      if (field.GetField()[head.second][head.first].GetType() ==
          CellType::FOOD) {
            if (flag3) {
              ++countFlood1;
              flag3 = false;
            }

            else {
              ++countFlood2;
            }
        
        
        snake.get().Grow();
        do {
          field.PlaceFood();
        } while (field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_BODY ||
                 field.GetField()[head.second][head.first].GetType() ==
                     CellType::SNAKE_HEAD);
      }

      flag3 = false;
    }

    // Обновляем карту с текущим состоянием змей
    field.UpdateMap(snake1, snake2);

    // Отрисовка
    // window.clear(); // Очистить экран

    // Добавим фоновое изображение
    static sf::Texture fonTexture;
    fonTexture.loadFromFile("../images/menu2.png");
    //----------------------------------------------------------------------

    sf::Image image = fonTexture.copyToImage();

    // Изменяем цвет определенных пикселей
    for (unsigned int x = 879; x < 920; ++x) {
      for (unsigned int y = 68; y < 109; ++y) {
        image.setPixel(x, y,
                       gameInfo.GetFirstPlayerInfo()
                           .GetColor()); // Устанавливаем красный цвет
      }
    }

    for (unsigned int x = 879; x < 920; ++x) {
      for (unsigned int y = 134; y < 175; ++y) {
        image.setPixel(x, y,
                       gameInfo.GetSecondPlayerInfo()
                           .GetColor()); // Устанавливаем красный цвет
      }
    }

    fonTexture.loadFromImage(image);

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
      p2.setPosition(940, 150); // Позиция текста на экране
      p2.setString("None");
      window.draw(p2); // Рисуем текст

    } else {
      sf::Text p2;
      p2.setFont(font);
      p2.setCharacterSize(24);           // Размер шрифта
      p2.setFillColor(sf::Color::White); // Цвет текста
      p2.setPosition(940, 150); // Позиция текста на экране
      p2.setString(gameInfo.GetSecondPlayerInfo().GetName());
      window.draw(p2); // Рисуем текст
    }

    sf::Text Round;
    std::string roundInfo = "Round: ";
    Round.setFont(font);
    Round.setCharacterSize(24);           // Размер шрифта
    Round.setFillColor(sf::Color::White); // Цвет текста
    Round.setPosition(940, 220); // Позиция текста на экране
    Round.setString(roundInfo + std::to_string(gameInfo.GetCurrentRound()));

    sf::Text Score1;
    std::string score1Info = "Score 1: ";
    Score1.setFont(font);
    Score1.setCharacterSize(24);           // Размер шрифта
    Score1.setFillColor(sf::Color::White); // Цвет текста
    Score1.setPosition(940, 290); // Позиция текста на экране
    Score1.setString(score1Info + std::to_string(countFlood1));

    sf::Text Score2;
    std::string score2Info = "Score 2: ";
    Score2.setFont(font);
    Score2.setCharacterSize(24);           // Размер шрифта
    Score2.setFillColor(sf::Color::White); // Цвет текста
    Score2.setPosition(940, 360); // Позиция текста на экране
    Score2.setString(score2Info + std::to_string(countFlood2));

    window.draw(p1);
    window.draw(Round);  // Рисуем текст
    window.draw(Score1); // Рисуем текст
    window.draw(Score2); // Рисуем текст

    window.display();

    //----------------------------------------------------------------------
    window.display();
    // Спрайт для фонового изображения
    static sf::Sprite fon_sprite;
    fon_sprite.setTexture(fonTexture);
    window.draw(fon_sprite);

    DrawMap(window, gameInfo, field); // Отрисовать карту
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

void ShowLegend(sf::RenderWindow &window, GameInfo &gameInfo, Field &field) {
  window.clear();

  sf::Texture legendTexture, obstacleTexture, klukvaTexture, p1Texture,
      p2Texture;
  std::string pathToP1, pathToP2;

  pathToP1 = ChoiceSelection(gameInfo.GetFirstPlayerInfo().GetColor());
  pathToP2 = ChoiceSelection(gameInfo.GetSecondPlayerInfo().GetColor());

  sf::Sprite legendSprite, obstacleSprite, klukvaSprite, p1Sprite, p2Sprite;
  legendTexture.loadFromFile("../images/Legend.png");
  obstacleTexture.loadFromFile("../images/obstacle.png");
  klukvaTexture.loadFromFile("../images/klukva.png");
  p1Texture.loadFromFile(pathToP1);
  p2Texture.loadFromFile(pathToP2);

  obstacleSprite.setTexture(obstacleTexture);
  obstacleSprite.setPosition(280, 330);

  klukvaSprite.setTexture(klukvaTexture);
  klukvaSprite.setPosition(280, 360);

  p1Sprite.setTexture(p1Texture);
  p1Sprite.setPosition(280, 240);

  p2Sprite.setTexture(p2Texture);
  p2Sprite.setPosition(280, 270);

  legendSprite.setTexture(legendTexture);

  sf::Font font;
  font.loadFromFile("../fonts/Consolas.ttf");

  sf::Text textGreeting1, textGreeting2, textP1, textP2, textObstacle,
      textKlukva, textStartGame1, textStartGame2;
  textGreeting1.setFont(font);
  textGreeting1.setCharacterSize(18); // Размер шрифта
  textGreeting1.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textGreeting1.setPosition(280, 170); // Позиция текста на экране
  textGreeting1.setString(
      "Welcome to my dungeon... Now you are facing the greatest challenge.");

  textGreeting2.setFont(font);
  textGreeting2.setCharacterSize(18);         // Размер шрифта
  textGreeting2.setFillColor(sf::Color::Red); // Цвет текста
  textGreeting2.setPosition(280, 190); // Позиция текста на экране
  textGreeting2.setString("Try to kill all my friends, ENEMY OF THE PEOPLE.");

  textP1.setFont(font);
  textP1.setCharacterSize(18);                 // Размер шрифта
  textP1.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textP1.setPosition(320, 240); // Позиция текста на экране
  textP1.setString("- Is that you, you little prankster.");

  textP2.setFont(font);
  textP2.setCharacterSize(18);                 // Размер шрифта
  textP2.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textP2.setPosition(320, 270); // Позиция текста на экране
  textP2.setString("- You'll be lucky if it's your friend and not mine.");

  textObstacle.setFont(font);
  textObstacle.setCharacterSize(18); // Размер шрифта
  textObstacle.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textObstacle.setPosition(320, 330); // Позиция текста на экране
  textObstacle.setString("- Murderous poison - especially for you HAHA.");

  textKlukva.setFont(font);
  textKlukva.setCharacterSize(18);                 // Размер шрифта
  textKlukva.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textKlukva.setPosition(320, 360); // Позиция текста на экране
  textKlukva.setString("- Delicious blue cranberries for my friends.");

  textStartGame1.setFont(font);
  textStartGame1.setCharacterSize(18);         // Размер шрифта
  textStartGame1.setFillColor(sf::Color::Red); // Цвет текста
  textStartGame1.setPosition(280, 440); // Позиция текста на экране
  textStartGame1.setString(
      "You will start moving after you press the control buttons.");

  textStartGame2.setFont(font);
  textStartGame2.setCharacterSize(18); // Размер шрифта
  textStartGame2.setFillColor(sf::Color(90, 255, 87)); // Цвет текста
  textStartGame2.setPosition(280, 480); // Позиция текста на экране
  textStartGame2.setString("press \"Space\" and die, friend))");

  window.draw(legendSprite);
  window.draw(textGreeting1);
  window.draw(textGreeting2);
  window.draw(p1Sprite);
  window.draw(p2Sprite);
  window.draw(obstacleSprite);
  window.draw(klukvaSprite);
  window.draw(textP1);
  window.draw(textP2);
  window.draw(textObstacle);
  window.draw(textKlukva);
  window.draw(textStartGame1);
  window.draw(textStartGame2);

  window.display();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        continue;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      return;
    }
  }
}