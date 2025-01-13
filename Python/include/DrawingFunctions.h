#pragma once
#include <time.h>
#include "functionsFullProject.h"

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfRounds()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(335, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfBots()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(791, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит на размер карты.
void DrawMapSize(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../fonts/Consolas.ttf");

	sf::Text mapSizeText(gameInfo.GetMapSize(), consolas, 24);
	mapSizeText.setFillColor(sf::Color::White);
	mapSizeText.setPosition(541, 322);
	window.draw(mapSizeText);
}

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow& window) {
	/*Создадим объект типа image и будем выгружать его в оконное приложение
	  Важно создавать объект, т.к. есть свойства, которые не всегда найдутся в текстуре.
	  К примеру маска цветов - можем игнорировать какие либо цвета объекта*/
	sf::Image pythonImage;
	pythonImage.loadFromFile("../images/pngwing.com.png");

	// Текстура и есть изображение. Можно не использовать Image (НО НЕЛЬЗЯ!!)
	sf::Texture pythonTexture;
	pythonTexture.loadFromImage(pythonImage);

	// Необходимо для выгрузки изображения в окно
	sf::Sprite pythonSprite;
	pythonSprite.setTexture(pythonTexture);
	pythonSprite.setPosition(20, 468);

	// На экран выводится змейка-талисман.
	window.draw(pythonSprite);
}

// Функция выводит в запись окно начального меню.
void DrawMainMenuWindow(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromFile("../images/Menu.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.draw(sprite);
}


// Функция выведет карту игры
void DrawMap(sf::RenderWindow& window, GameInfo& gameInfo, Field& field) {
    // Загрузка текстур
    sf::Image snakeImage, foodImage, obstacleImage, cellImage;
    snakeImage.loadFromFile("../images/headSnake.png");
    foodImage.loadFromFile("../images/klukva.png");
    obstacleImage.loadFromFile("../images/obstacle.png");
    cellImage.loadFromFile("../images/cell.png");

    // Текстуры
    sf::Texture snakeTexture, foodTexture, obstacleTexture, cellTexture;
    snakeTexture.loadFromImage(snakeImage);
    foodTexture.loadFromImage(foodImage);
    obstacleTexture.loadFromImage(obstacleImage);
    cellTexture.loadFromImage(cellImage);

    // Сприты
    sf::Sprite snake_head(snakeTexture);
    sf::Sprite snake_body(cellTexture);
    sf::Sprite snake_tail(cellTexture);
    sf::Sprite food(foodTexture);
    sf::Sprite obstacle(obstacleTexture);

    // Установка начальной позиции еды
    food.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);

    Snake snake(20, 20);
    snake_head.setTextureRect(sf::IntRect(0, 0, 20, 20));

    // Основной игровой цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        // Управление направлением змейки
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && snake.GetDirection() != std::make_pair(0.f, 0.1f)) {
            snake.SetDirection(0, -0.1);
            snake_head.setTextureRect(sf::IntRect(0, 0, 20, 20)); // Текстура для головы вверх
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && snake.GetDirection() != std::make_pair(0.f, -0.1f)) {
            snake.SetDirection(0, 0.1);
            snake_head.setTextureRect(sf::IntRect(74, 0, 20, 20)); // Текстура для головы вниз
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && snake.GetDirection() != std::make_pair(0.1f, 0.f)) {
            snake.SetDirection(-0.1, 0);
            snake_head.setTextureRect(sf::IntRect(148, 0, 20, 20)); // Текстура для головы влево
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && snake.GetDirection() != std::make_pair(-0.1f, 0.f)) {
            snake.SetDirection(0.1, 0);
            snake_head.setTextureRect(sf::IntRect(222, 0, 20, 20)); // Текстура для головы вправо
        }

        // Устанавливаем позицию головы змейки в зависимости от направления
        snake_head.setPosition(snake._body[0].first, snake._body[0].second);

        // Перемещение змейки
        snake.MoveSnake();

        // Проверка на столкновение с границами окна
        auto head = snake._body.front();
        if (head.first < 0 || head.first >= window.getSize().x || head.second < 0 || head.second >= window.getSize().y) {
            window.clear(sf::Color::Black);
            window.display();
            return;
        }

        // Проверка на столкновение с самой собой
        for (size_t i = 1; i < snake._body.size(); ++i) {
            if (head == snake._body[i]) {
                window.clear(sf::Color::Black);
                window.display();
                return;
            }
        }

        // Проверка на столкновение с препятствием
        if (head.first >= obstacle.getPosition().x && head.first < obstacle.getPosition().x + obstacleTexture.getSize().x &&
            head.second >= obstacle.getPosition().y && head.second < obstacle.getPosition().y + obstacleTexture.getSize().y) {
            window.clear(sf::Color::Black);
            window.display();
            return;
        }

        // Проверка на съедание еды
        if (head.first >= food.getPosition().x && head.first <= food.getPosition().x + foodTexture.getSize().x &&
            head.second >= food.getPosition().y && head.second <= food.getPosition().y + foodTexture.getSize().y) {
            // Добавляем новую ячейку в тело змейки
            snake.Grow();

            // Перемещаем еду на новое место
            food.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);

            // Изменяем направление змейки после съедания еды
            if (snake.GetDirection() == std::make_pair(0.f, 0.1f)) {
                snake.SetDirection(0, -0.1);  // вверх
            } else if (snake.GetDirection() == std::make_pair(0.f, -0.1f)) {
                snake.SetDirection(0, 0.1);   // вниз
            } else if (snake.GetDirection() == std::make_pair(-0.1f, 0.f)) {
                snake.SetDirection(0.1, 0);   // вправо
            } else if (snake.GetDirection() == std::make_pair(0.1f, 0.f)) {
                snake.SetDirection(-0.1, 0);  // влево
            }
        }

        // Отрисовка
        window.clear();

        // Отрисовка препятствия
        window.draw(obstacle);

        // Отрисовка еды
        window.draw(food);

        // Отрисовка частей змейки
        for (size_t i = 0; i < snake._body.size(); ++i) {
            if (i == 0) {
                window.draw(snake_head);
            } else {
                snake_body.setPosition(snake._body[i].first, snake._body[i].second);
                window.draw(snake_body);
            }
        }

        window.display();
    }
}

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Texture texture;
	texture.loadFromFile("../images/Start.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.draw(sprite);

	// На экран выводится информация о выбранных значениях счетчиков.
	DrawNumberOfRounds(window, gameInfo);
	DrawNumberOfBots(window, gameInfo);
	DrawMapSize(window, gameInfo);
}

// Функция выводит экран выхода из игры.
void DrawLeaveGameWindow(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromFile("../images/Leave.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.draw(sprite);
}

// Функция выводит экран настроек.
void DrawSettingsWindow(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Texture texture;
	texture.loadFromFile("../images/Settings.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.draw(sprite);
}

// Функция выводит экран настроек.
void DrawAuthorsWindow(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromFile("../images/Authors.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.draw(sprite);
}

// Функция осуществляет переход с экрана главного меню на экран начала игры.
void MoveWindowFromMainToStart(sf::RenderWindow& window) {

	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Start.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2 + 648);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter(1152 / 2, (int)(648 / 2 + 648 - ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 648));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана главного меню на экран начала игры.
void MoveWindowFromStartToMain(sf::RenderWindow& window) {

	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Start.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2), (int)(648 / 2 + ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 648));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана главного меню на экран выхода из игры.
void MoveWindowFromMainToLeaveGame(sf::RenderWindow& window) {
	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Leave.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2 + ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 1152), (int)(648 / 2));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана главного меню на экран выхода из игры.
void MoveWindowFromLeaveGameToMain(sf::RenderWindow& window) {
	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Leave.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2 + 1152, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2 + 1152 - ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 1152), (int)(648 / 2));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана главного меню на экран настроек игры.
void MoveWindowFromMainToSettings(sf::RenderWindow& window) {
	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Settings.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2 + 1152, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2 + 1152 - ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 1152), (int)(648 / 2));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана настроек на экран главного меню.
void MoveWindowFromSettingsToMain(sf::RenderWindow& window) {
	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Settings.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2 + ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 1152), (int)(648 / 2));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана главного меню на экран авторов игры.
void MoveWindowFromMainToAuthors(sf::RenderWindow& window) {

	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Authors.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2 + 648);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter(1152 / 2, (int)(648 / 2 + ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 648));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}

// Функция осуществляет переход с экрана авторов игры на экран главного меню.
void MoveWindowFromAuthorsToMain(sf::RenderWindow& window) {

	// Создается камера.
	sf::View view(sf::FloatRect(0, 648, 1152, 648));

	// На экран выводится изображение, связывающее главное меню и меню начала игры.
	sf::Texture texture;
	texture.loadFromFile("../images/Menu-Authors.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	window.clear();
	window.draw(sprite);	
	view.setCenter(1152 / 2, 648 / 2);

	// Задаются часы.
	sf::Clock clock;
	sf::Time startTime = clock.getElapsedTime();

	// Камера двигается относительно изображения.
	while (clock.getElapsedTime() - startTime < sf::seconds(3.24)) {
		view.setCenter((int)(1152 / 2), (int)(648 / 2 + 648 - ((clock.getElapsedTime() - startTime) / sf::seconds(3.24)) * 648));
		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.display();
	}

	// Камера возвращается в исходное положение.
	view.setCenter(1152 / 2, 648 / 2);
	window.clear();
	window.setView(view);
	window.display();
}