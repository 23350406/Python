#pragma once

#include "functionsFullProject.h"
#include <SFML/Window/Keyboard.hpp>

// Функция определяет: является ли действие нажатием на левую кнопку мыши.
bool isLMC(sf::Event &event, GameInfo &gameInfo) {
  // Если пользователь нажал не на мышку, то false.
  if (event.type != sf::Event::MouseButtonPressed) {
    return false;
  }

  // Если кнопка мыши не левая - false.
  if (event.mouseButton.button != sf::Mouse::Left) {
    return false;
  }

  // Если кнопка только нажалась - возвращается true.
  return true;
}

// Функция определяет: было ли действие в прямоугольнике заданном координатами.
bool isInBox(sf::Event &event, int x1, int y1, int x2, int y2) {
  return event.mouseButton.x >= x1 && event.mouseButton.x <= x2 &&
         event.mouseButton.y >= y1 && event.mouseButton.y <= y2;
}

void ChangeWindowToStartGameWindow(sf::RenderWindow &window,
                                   GameInfo &gameInfo) {
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("StartGame");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится экран выбора настроек старта игры.
  DrawStartGameWindow(window, gameInfo);

  // Записанное в вывод показывается пользователю.
  window.display();
}

void ChangeWindowToGameWindow(sf::RenderWindow &window, GameInfo &gameInfo,
                              Field &field) {
  // Устанавливаем текущий экран игры
  gameInfo.SetCurrentWindowName("Game");

  // Очищаем экран
  window.clear(sf::Color::Black);

  // Инициализация случайного генератора
  srand(static_cast<unsigned>(time(0)));

  // Генерация начальных координат змей
  auto GenerateValidPositionForSnake =
      [&](Field &field) -> std::vector<std::pair<int, int>> {
    std::vector<std::pair<int, int>> positions;
    do {
      positions.clear();
      for (int i = 0; i < 3; ++i) {
        int x = rand() % field.GetWidth();
        int y = rand() % field.GetHeight();
        if (field.GetField()[y][x].GetType() == CellType::EMPTY)
          positions.emplace_back(x, y);
        else
          break;
      }
    } while (positions.size() < 3);

    return positions;
  };

  if (gameInfo.GetIsSolo()) {
    // Создаем вектор змей
    std::vector<Snake> snakes;

    // Добавляем игрока
    auto playerSnakePos = GenerateValidPositionForSnake(field);
    Snake snakePlayer(playerSnakePos[0].first, playerSnakePos[1].second);
    snakePlayer.Grow(); // Первое увеличение змеи
    snakePlayer.Grow(); // Второе увеличение змеи

    // Добавляем змей для ботов
    for (int i = 0; i < gameInfo.GetNumberOfBots(); ++i) {
      auto botSnakePos = GenerateValidPositionForSnake(field);
      Snake botSnake(botSnakePos[0].first, botSnakePos[0].second);
      botSnake.Grow(); // Змейка растёт
      botSnake.Grow(); // Еще одна клетка для бота
      snakes.emplace_back(botSnake);
    }

    // Однопользовательский игровой цикл
    GameLoop(window, gameInfo, field, snakePlayer, snakes);
    return;
  }

  // Если многопользовательская игра
  if (!gameInfo.GetIsSolo()) {
    auto firstSnakePos = GenerateValidPositionForSnake(field);
    auto secondSnakePos = GenerateValidPositionForSnake(field);

    Snake firstSnake(firstSnakePos[0].first, firstSnakePos[0].second);
    Snake secondSnake(secondSnakePos[0].first, secondSnakePos[0].second);

    firstSnake.Grow(); // Змейка первой игрока растёт
    firstSnake.Grow(); // Две клетки

    secondSnake.Grow(); // Змейка второй игрока растёт
    secondSnake.Grow(); // Две клетки

    // Игровой цикл для двух игроков
    GameLoop(window, gameInfo, field, firstSnake, secondSnake);
    return;
  }
}

void ChangeWindowToMainMenuWindow(sf::RenderWindow &window,
                                  GameInfo &gameInfo) {
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("MainMenu");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится главное меню.
  DrawMainMenuWindow(window);

  // Записанное в вывод показывается пользователю.
  window.display();
}

void ChangeWindowToLeaveGameWindow(sf::RenderWindow &window,
                                   GameInfo &gameInfo) {
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("LeaveGame");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится окно выхода из игры.
  DrawLeaveGameWindow(window);

  // Записанное в вывод показывается пользователю.
  window.display();
}

void ChangeWindowToSettingsWindow(sf::RenderWindow &window,
                                  GameInfo &gameInfo) {
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("Settings");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится меню настроек.
  DrawSettingsWindow(window, gameInfo);

  // Записанное в вывод показывается пользователю.
  window.display();
}

void ChangeWindowToAuthorsWindow(sf::RenderWindow &window, GameInfo &gameInfo) {
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("Authors");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится меню настроек.
  DrawAuthorsWindow(window);

  Show(window);

  // Записанное в вывод показывается пользователю.
  window.display();
}

// Функция обрабатывает событие на экране главного меню.
void ProcessActionInMainMenu(sf::RenderWindow &window, sf::Event &event,
                             GameInfo &gameInfo) {

  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();

    // Пользователь нажал ЛКМ на кнопку "START" -> переход на страницу настроек
    // старта игры.
    if (isInBox(event, 426, 50, 726, 210)) {

      // Переход между главным меню и меню начала игры.
      MoveWindowFromMainToStart(window);
      ChangeWindowToStartGameWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ на кнопку "LEAVE" -> переход на страницу выхода из
    // игры.
    if (isInBox(event, 725, 309, 1026, 498)) {

      // Переход между главным меню и меню выхода из игры.
      MoveWindowFromMainToLeaveGame(window);
      ChangeWindowToLeaveGameWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ на кнопку "SETTINGS" -> переход на страницу
    // настроек.
    if (isInBox(event, 126, 320, 426, 499)) {

      // Функция осуществляет переход с экрана главного меню на экран настроек
      // игры.
      MoveWindowFromMainToSettings(window);
      ChangeWindowToSettingsWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ на кнопку авторов -> переход на страницу авторов.
    if (isInBox(event, 499, 490, 652, 648)) {

      // Функция осуществляет переход с экрана главного меню на экран авторов
      // игры.
      MoveWindowFromMainToAuthors(window);
      ChangeWindowToAuthorsWindow(window, gameInfo);
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProcessActionInStartGameMenu(sf::RenderWindow &window, sf::Event &event,
                                  GameInfo &gameInfo) {

  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();

    // Пользователь нажал ЛКМ на кнопку назад -> переход на страницу главного
    // меню игры.
    if (isInBox(event, 18, 13, 133, 74)) {
      // Переход между главным меню и меню начала игры.
      MoveWindowFromStartToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    // Пользователь уменьшил количество раундов.
    if (isInBox(event, 197, 120, 247, 170)) {
      gameInfo.DecreaseNumberOfRounds();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь увеличил количество раундов.
    if (isInBox(event, 436, 120, 486, 170)) {
      gameInfo.IncreaseNumberOfRounds();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь уменьшил количество ботов.
    if (isInBox(event, 651, 120, 701, 170)) {
      gameInfo.DecreaseNumberOfBots();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь увеличил количество ботов.
    if (isInBox(event, 891, 120, 941, 170)) {
      gameInfo.IncreaseNumberOfBots();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь уменьшил размер карты.
    if (isInBox(event, 432, 314, 482, 364)) {
      gameInfo.DecreaseMapSize();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь увеличил размер карты.
    if (isInBox(event, 671, 314, 721, 364)) {
      gameInfo.IncreaseMapSize();
      window.clear();
      DrawStartGameWindow(window, gameInfo);
      window.display();
    }

    // Пользователь нажал ЛКМ на кнопку выбора режима игры.
    if (isInBox(event, 960, 200, 1020, 260)) {

      sf::Texture soloTexture;
      // Изменяется значение режима игры.
      if (!gameInfo.GetIsSolo()) {
        gameInfo.SetSolo();
        window.clear(); // Старое окно стирается.
        DrawStartGameWindow(window,
                            gameInfo); // Окно начала игры перерисовывается и
                                       // выводится на экран.
      } else {
        gameInfo.SetDuo();
        gameInfo.DecreaseNumberOfBots(); // Для многопользовательской игры
                                         // выставляется значение ботов на 0.
        gameInfo.DecreaseNumberOfBots();
        gameInfo.DecreaseNumberOfBots();
        window.clear(); // Старое окно стирается.
        DrawStartGameWindow(window,
                            gameInfo); // Окно начала игры перерисовывается и
                                       // выводится на экран.
      }
      // Режим игры выводится на экран
      sf::Sprite soloSprite(soloTexture);
      soloSprite.setPosition(960, 200);
      window.draw(soloSprite);
      window.display();
    }

    if (isInBox(event, 432, 466, 722, 645)) {
      for (int i = 0; i < gameInfo.GetNumberOfRounds(); ++i) {
        vector<int> temp = DefineParametersForField(gameInfo);
        Field fieldInfo(temp[0], temp[1]);

        gameInfo.SetCurrentRound(i + 1);
        if (i == 0) {
          gameInfo.SetCurrentWindowName("Legend");
          ShowLegend(window, gameInfo, fieldInfo);
        }
        ChangeWindowToGameWindow(window, gameInfo, fieldInfo);
      }
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProcessActionInLeaveGameMenu(sf::RenderWindow &window, sf::Event &event,
                                  GameInfo &gameInfo) {

  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();

    // Пользователь нажал ЛКМ на стрелку назад -> переход на главное меню.
    if (isInBox(event, 16, 0, 131, 60)) {

      // Переход между главным меню и меню выхода из игры.
      MoveWindowFromLeaveGameToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ на кнопку "NO" -> переход на главное меню.
    if (isInBox(event, 746, 318, 1048, 498)) {

      // Переход между главным меню и меню выхода из игры.
      MoveWindowFromLeaveGameToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ на кнопку "YES" -> выход из игры.
    if (isInBox(event, 98, 318, 400, 498)) {
      window.close();
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProcessActionInSettingsMenu(sf::RenderWindow &window, sf::Event &event,
                                 GameInfo &gameInfo) {
  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();

    // Пользователь нажал ЛКМ на стрелку назад -> переход на главное меню.
    if (isInBox(event, 7, 10, 122, 71)) {
      gameInfo.SaveToFile("conf.txt");
      // Функция осуществляет переход с экрана настроек игры на экран главного
      // меню.
      MoveWindowFromSettingsToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    // Пользователь нажал ЛКМ по кнопке "вверх" для первого игрока - она
    // становится изменяемой.
    if (isInBox(event, 204, 106, 258, 160)) {
      gameInfo.SetFieldInUse("P1-Up");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "влево" для первого игрока - она
    // становится изменяемой.
    if (isInBox(event, 148, 162, 202, 214)) {
      gameInfo.SetFieldInUse("P1-Left");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "вправо" для первого игрока - она
    // становится изменяемой.
    if (isInBox(event, 204, 162, 258, 214)) {
      gameInfo.SetFieldInUse("P1-Down");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "вниз" для первого игрока - она
    // становится изменяемой.
    if (isInBox(event, 262, 162, 318, 214)) {
      gameInfo.SetFieldInUse("P1-Right");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "вверх" для второго игрока - она
    // становится изменяемой.
    if (isInBox(event, 204, 340, 258, 394)) {
      gameInfo.SetFieldInUse("P2-Up");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "влево" для второго игрока - она
    // становится изменяемой.
    if (isInBox(event, 148, 396, 202, 448)) {
      gameInfo.SetFieldInUse("P2-Left");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "вправо" для второго игрока - она
    // становится изменяемой.
    if (isInBox(event, 204, 396, 258, 448)) {
      gameInfo.SetFieldInUse("P2-Down");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "вниз" для второго игрока - она
    // становится изменяемой.
    if (isInBox(event, 262, 396, 318, 448)) {
      gameInfo.SetFieldInUse("P2-Right");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "имя" для первого игрока - она
    // становится изменяемой.
    if (isInBox(event, 416, 150, 614, 212)) {
      gameInfo.SetFieldInUse("P1-Name");
      return;
    }

    // Пользователь нажал ЛКМ по кнопке "имя" для второго игрока - она
    // становится изменяемой.
    if (isInBox(event, 416, 380, 614, 436)) {
      gameInfo.SetFieldInUse("P2-Name");
      return;
    }

    // Считывается информация об игроках.
    PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
    PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();

    // Задаются игровые цвета.
    sf::Color red(255, 0, 0);
    sf::Color orange(233, 148, 0);
    sf::Color yellow(255, 246, 0);
    sf::Color lime(84, 255, 0);
    sf::Color cyan(0, 255, 234);
    sf::Color purple(120, 0, 255);
    sf::Color magenta(255, 0, 162);
    sf::Color white(255, 255, 229);

    // Для каждой ячейки цвета проверяется нажато ли туда, занята ли она и если
    // нет, то она становится новым цветом.
    if (isInBox(event, 704, 96, 758, 156)) {
      if (secondPlayerInfo.GetColor() != red &&
          firstPlayerInfo.GetColor() != red) {
        firstPlayerInfo.SetColor(red);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 758, 96, 812, 156)) {
      if (secondPlayerInfo.GetColor() != orange &&
          firstPlayerInfo.GetColor() != orange) {
        firstPlayerInfo.SetColor(orange);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 812, 96, 866, 156)) {
      if (secondPlayerInfo.GetColor() != yellow &&
          firstPlayerInfo.GetColor() != yellow) {
        firstPlayerInfo.SetColor(yellow);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 866, 96, 920, 156)) {
      if (secondPlayerInfo.GetColor() != lime &&
          firstPlayerInfo.GetColor() != lime) {
        firstPlayerInfo.SetColor(lime);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 704, 156, 758, 216)) {
      if (secondPlayerInfo.GetColor() != cyan &&
          firstPlayerInfo.GetColor() != cyan) {
        firstPlayerInfo.SetColor(cyan);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 758, 156, 812, 216)) {
      if (secondPlayerInfo.GetColor() != purple &&
          firstPlayerInfo.GetColor() != purple) {
        firstPlayerInfo.SetColor(purple);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 812, 156, 866, 216)) {
      if (secondPlayerInfo.GetColor() != magenta &&
          firstPlayerInfo.GetColor() != magenta) {
        firstPlayerInfo.SetColor(magenta);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 866, 156, 920, 216)) {
      if (secondPlayerInfo.GetColor() != white &&
          firstPlayerInfo.GetColor() != white) {
        firstPlayerInfo.SetColor(white);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      }
    }
    if (isInBox(event, 704, 336, 758, 396)) {
      if (secondPlayerInfo.GetColor() != red &&
          firstPlayerInfo.GetColor() != red) {
        secondPlayerInfo.SetColor(red);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 758, 336, 812, 396)) {
      if (secondPlayerInfo.GetColor() != orange &&
          firstPlayerInfo.GetColor() != orange) {
        secondPlayerInfo.SetColor(orange);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 812, 336, 866, 396)) {
      if (secondPlayerInfo.GetColor() != yellow &&
          firstPlayerInfo.GetColor() != yellow) {
        secondPlayerInfo.SetColor(yellow);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 866, 336, 920, 396)) {
      if (secondPlayerInfo.GetColor() != lime &&
          firstPlayerInfo.GetColor() != lime) {
        secondPlayerInfo.SetColor(lime);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 704, 396, 758, 456)) {
      if (secondPlayerInfo.GetColor() != cyan &&
          firstPlayerInfo.GetColor() != cyan) {
        secondPlayerInfo.SetColor(cyan);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 758, 396, 812, 456)) {
      if (secondPlayerInfo.GetColor() != purple &&
          firstPlayerInfo.GetColor() != purple) {
        secondPlayerInfo.SetColor(purple);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 812, 396, 866, 456)) {
      if (secondPlayerInfo.GetColor() != magenta &&
          firstPlayerInfo.GetColor() != magenta) {
        secondPlayerInfo.SetColor(magenta);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }
    if (isInBox(event, 866, 396, 920, 456)) {
      if (secondPlayerInfo.GetColor() != white &&
          firstPlayerInfo.GetColor() != white) {
        secondPlayerInfo.SetColor(white);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      }
    }

    gameInfo.SetFieldInUse("");
    return;
  }

  // Если пользователь нажал клавишу на клавиатуре.
  sf::Keyboard::Key pressedKey = GetPressedKey();
  if (pressedKey) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      pressedKey = sf::Keyboard::A;
    }
    // Определяется изменяемое поле.
    std::string fieldInUse = gameInfo.GetFieldInUse();

    // Если клавиша не используется в управлении, то она меняет нужное
    // управление.
    if (keyIsntUsed(gameInfo, pressedKey)) {
      if (fieldInUse == "P1-Up") {
        PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
        firstPlayerInfo.SetUpKey(pressedKey);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P1-Right") {
        PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
        firstPlayerInfo.SetRightKey(pressedKey);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P1-Left") {
        PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
        firstPlayerInfo.SetLeftKey(pressedKey);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P1-Down") {
        PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
        firstPlayerInfo.SetDownKey(pressedKey);
        gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P2-Up") {
        PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();
        secondPlayerInfo.SetUpKey(pressedKey);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P2-Right") {
        PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();
        secondPlayerInfo.SetRightKey(pressedKey);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P2-Left") {
        PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();
        secondPlayerInfo.SetLeftKey(pressedKey);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
      if (fieldInUse == "P2-Down") {
        PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();
        secondPlayerInfo.SetDownKey(pressedKey);
        gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
        // Сбрасывается используемое поле.
        gameInfo.SetFieldInUse("");
      }
    }

    // Если изменяются имена игроков.
    if (fieldInUse == "P1-Name") {
      PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();

      // Имя меняется в соответствии с нажатой клавишей.
      std::string playerName = firstPlayerInfo.GetName();
      if (playerName.size() > 0 && pressedKey == sf::Keyboard::BackSpace) {
        playerName.pop_back();
      }
      if (playerName.size() < 10 && pressedKey != sf::Keyboard::BackSpace) {
        playerName.append(GetKeyboardCharacter(pressedKey));
      }
      firstPlayerInfo.SetName(playerName);
      gameInfo.SetFirstPlayerInfo(firstPlayerInfo);
      std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    if (fieldInUse == "P2-Name") {
      PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();

      // Имя меняется в соответствии с нажатой клавишей.
      std::string playerName = secondPlayerInfo.GetName();
      if (playerName.size() > 0 && pressedKey == sf::Keyboard::BackSpace) {
        playerName.pop_back();
      }
      if (playerName.size() < 10 && pressedKey != sf::Keyboard::BackSpace) {
        playerName.append(GetKeyboardCharacter(pressedKey));
      }
      secondPlayerInfo.SetName(playerName);
      gameInfo.SetSecondPlayerInfo(secondPlayerInfo);
      std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
  }

  gameInfo.UnsetPressedButton();

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится меню настроек.
  DrawSettingsWindow(window, gameInfo);

  // Записанное в вывод показывается пользователю.
  window.display();
}

void ProcessActionInAuthorsMenu(sf::RenderWindow &window, sf::Event &event,
                                GameInfo &gameInfo) {
  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();

    // Пользователь нажал ЛКМ на стрелку назад -> переход на главное меню.
    if (isInBox(event, 7, 10, 122, 71)) {

      // Функция осуществляет переход с экрана авторов игры на экран главного
      // меню.
      MoveWindowFromAuthorsToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProccessActionGameOver(sf::RenderWindow &window, sf::Event &event,
                            GameInfo &gameInfo) {

  // Если пользователь нажал ЛКМ.
  if (isLMC(event, gameInfo)) {

    if (gameInfo.GetPressedButton()) {
      return;
    }

    gameInfo.SetPressedButton();
    // Пользователь нажал ЛКМ на кнопку назад -> переход на страницу главного
    // меню игры.
    // Menu
    if (isInBox(event, 430, 500, 730, 572)) {
      // Переход между главным меню и меню начала игры.
      // MoveWindowFromStartToMain(window);
      gameInfo.LoadFromFile("conf.txt");
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }
    // Restart
    if (isInBox(event, 430, 390, 730, 465)) {
      gameInfo.LoadFromFile("conf.txt");
      for (int i = 0; i < gameInfo.GetNumberOfRounds(); ++i) {
        vector<int> temp = DefineParametersForField(gameInfo);
        Field fieldInfo(temp[0], temp[1]);

        gameInfo.SetCurrentRound(i + 1);
        ChangeWindowToGameWindow(window, gameInfo, fieldInfo);
      }
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProcessEvent(sf::RenderWindow &window, sf::Event &event,
                  GameInfo &gameInfo) {
  if (gameInfo.GetCurrentWindowName() == "MainMenu") {
    ProcessActionInMainMenu(window, event, gameInfo);
    return;
  }

  if (gameInfo.GetCurrentWindowName() == "StartGame") {
    gameInfo.SaveToFile("conf.txt");
    ProcessActionInStartGameMenu(window, event, gameInfo);

    return;
  }

  if (gameInfo.GetCurrentWindowName() == "LeaveGame") {
    ProcessActionInLeaveGameMenu(window, event, gameInfo);
    return;
  }

  if (gameInfo.GetCurrentWindowName() == "Settings") {
    ProcessActionInSettingsMenu(window, event, gameInfo);
    return;
  }

  if (gameInfo.GetCurrentWindowName() == "Authors") {
    ProcessActionInAuthorsMenu(window, event, gameInfo);
    return;
  }

  if (gameInfo.GetCurrentWindowName() == "GameOver") {
    ProccessActionGameOver(window, event, gameInfo);
    return;
  }
}

// Функция возвращает строковую запись кнопки с клавиатуры.
std::string GetKeyboardCharacter(sf::Keyboard::Key key) {
  switch (key) {
  case sf::Keyboard::A:
    return "A";
  case sf::Keyboard::B:
    return "B";
  case sf::Keyboard::C:
    return "C";
  case sf::Keyboard::D:
    return "D";
  case sf::Keyboard::E:
    return "E";
  case sf::Keyboard::F:
    return "F";
  case sf::Keyboard::G:
    return "G";
  case sf::Keyboard::H:
    return "H";
  case sf::Keyboard::I:
    return "I";
  case sf::Keyboard::J:
    return "J";
  case sf::Keyboard::K:
    return "K";
  case sf::Keyboard::L:
    return "L";
  case sf::Keyboard::M:
    return "M";
  case sf::Keyboard::N:
    return "N";
  case sf::Keyboard::O:
    return "O";
  case sf::Keyboard::P:
    return "P";
  case sf::Keyboard::Q:
    return "Q";
  case sf::Keyboard::R:
    return "R";
  case sf::Keyboard::S:
    return "S";
  case sf::Keyboard::T:
    return "T";
  case sf::Keyboard::U:
    return "U";
  case sf::Keyboard::V:
    return "V";
  case sf::Keyboard::W:
    return "W";
  case sf::Keyboard::X:
    return "X";
  case sf::Keyboard::Y:
    return "Y";
  case sf::Keyboard::Z:
    return "Z";
  case sf::Keyboard::Num0:
    return "0";
  case sf::Keyboard::Num1:
    return "1";
  case sf::Keyboard::Num2:
    return "2";
  case sf::Keyboard::Num3:
    return "3";
  case sf::Keyboard::Num4:
    return "4";
  case sf::Keyboard::Num5:
    return "5";
  case sf::Keyboard::Num6:
    return "6";
  case sf::Keyboard::Num7:
    return "7";
  case sf::Keyboard::Num8:
    return "8";
  case sf::Keyboard::Num9:
    return "9";
  case sf::Keyboard::Up:
    return "^";
  case sf::Keyboard::Down:
    return "v";
  case sf::Keyboard::Left:
    return "<";
  case sf::Keyboard::Right:
    return ">";
  case sf::Keyboard::Comma:
    return ",";
  case sf::Keyboard::Backspace:
    return "<-";
  default:
    return "";
  }
}

// Функция возвращает нажатую кнопку клавиатуры.
sf::Keyboard::Key GetPressedKey() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    return sf::Keyboard::Divide;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
    return sf::Keyboard::B;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
    return sf::Keyboard::C;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    return sf::Keyboard::D;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    return sf::Keyboard::E;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    return sf::Keyboard::F;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
    return sf::Keyboard::G;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
    return sf::Keyboard::H;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
    return sf::Keyboard::I;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
    return sf::Keyboard::J;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    return sf::Keyboard::K;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    return sf::Keyboard::L;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
    return sf::Keyboard::M;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
    return sf::Keyboard::N;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
    return sf::Keyboard::O;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
    return sf::Keyboard::P;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    return sf::Keyboard::Q;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    return sf::Keyboard::R;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    return sf::Keyboard::S;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
    return sf::Keyboard::T;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
    return sf::Keyboard::U;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
    return sf::Keyboard::V;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    return sf::Keyboard::W;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
    return sf::Keyboard::X;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
    return sf::Keyboard::Y;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
    return sf::Keyboard::Z;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
    return sf::Keyboard::Num0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
    return sf::Keyboard::Num1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
    return sf::Keyboard::Num2;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
    return sf::Keyboard::Num3;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
    return sf::Keyboard::Num4;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
    return sf::Keyboard::Num5;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
    return sf::Keyboard::Num6;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
    return sf::Keyboard::Num7;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
    return sf::Keyboard::Num8;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
    return sf::Keyboard::Num9;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    return sf::Keyboard::Up;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    return sf::Keyboard::Down;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return sf::Keyboard::Right;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return sf::Keyboard::Left;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
    return sf::Keyboard::Comma;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    return sf::Keyboard::BackSpace;
  }
}

// Функция проверяет, что клавиша не используется в управлении.
bool keyIsntUsed(GameInfo &gameInfo, sf::Keyboard::Key keyToUse) {

  // Получается информация об игроках.
  PlayerInfo firstPlayerInfo = gameInfo.GetFirstPlayerInfo();
  PlayerInfo secondPlayerInfo = gameInfo.GetSecondPlayerInfo();
  // Для каждой из используемых в управлении клавиш проверяется, что новая
  // клавиша с ней не совпадает.
  if (firstPlayerInfo.GetUpKey() == keyToUse) {
    return false;
  }
  if (firstPlayerInfo.GetRightKey() == keyToUse) {
    return false;
  }
  if (firstPlayerInfo.GetLeftKey() == keyToUse) {
    return false;
  }
  if (firstPlayerInfo.GetDownKey() == keyToUse) {
    return false;
  }
  if (secondPlayerInfo.GetUpKey() == keyToUse) {
    return false;
  }
  if (secondPlayerInfo.GetRightKey() == keyToUse) {
    return false;
  }
  if (secondPlayerInfo.GetLeftKey() == keyToUse) {
    return false;
  }
  if (secondPlayerInfo.GetDownKey() == keyToUse) {
    return false;
  }
  return true;
}
