#include "../include/fileForLink.h"

int main() {

  // Открывается окно для вывода
  sf::RenderWindow window(sf::VideoMode(1152, 648), "Python");
  window.setSize(sf::Vector2u(1152, 648));

  // Экран закрашивается черным.
  window.clear(sf::Color::Black);

  // В вывод на экран заносится главное меню.
  DrawMainMenuWindow(window);

  // Записанное в вывод показывается пользователю.
  window.display();

  // Создается массив с информацией об игре.
  GameInfo gameInfo;

  // Постоянное обновление картинки
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        continue;
      }
    }

    // Обрабатывается событие.
    ProcessEvent(window, event, gameInfo);
  }

  return 0;
}