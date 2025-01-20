#pragma once

#include "functionsFullProject.h"

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
  // Записывается название экрана игры, на который перешел пользователь.
  gameInfo.SetCurrentWindowName("Game");

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // Инициализируем змейку с произвольной начальной позицией (например, в центре
  // поля)
  int startX = field.GetWidth() / 2;
  int startY = field.GetHeight() / 2;
  Snake snake(startX, startY);

  // Запускаем игровой цикл, передавая окно, информацию об игре, поле и змейку
  GameLoop(window, gameInfo, field, snake);

  // Записанное в вывод показывается пользователю.
  window.display();
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

    if (isInBox(event, 432, 466, 722, 645)) {
      vector<int> temp = DefineParametersForField(gameInfo);
      Field fieldInfo(temp[0], temp[1]);

      ChangeWindowToGameWindow(window, gameInfo, fieldInfo);
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

      // Функция осуществляет переход с экрана настроек игры на экран главного
      // меню.
      MoveWindowFromSettingsToMain(window);
      ChangeWindowToMainMenuWindow(window, gameInfo);
    }

    return;
  }

  gameInfo.UnsetPressedButton();
}

void ProcessActionInGame(sf::RenderWindow &window, sf::Event &event,
                         GameInfo &gameInfo) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::W) {
    }
  }
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

void ProcessEvent(sf::RenderWindow &window, sf::Event &event,
                  GameInfo &gameInfo) {
  if (gameInfo.GetCurrentWindowName() == "MainMenu") {
    ProcessActionInMainMenu(window, event, gameInfo);
    return;
  }

  if (gameInfo.GetCurrentWindowName() == "StartGame") {
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

  if (gameInfo.GetCurrentWindowName() == "Game") {
    ProcessActionInGame(window, event, gameInfo);
    return;
  }
}
