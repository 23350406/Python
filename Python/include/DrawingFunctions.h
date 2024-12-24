#pragma once

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

	vector<vector<Cell>> myMap = field.GetField();
	sf::Texture texture;
	sf::Sprite sprite;

	for (int i = 0; i < field.GetHeight() - 1; ++i) {
		for (int j = 0; j < field.GetWidth() - 1; ++j) {
			texture.loadFromImage(myMap[i][j].GetImage());
			sprite.setTexture(texture);
			sprite.setPosition(280 + 20 * i, 50 + 20 * j);
			window.draw(sprite);
		}
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
