#pragma once

#include "GameInfo.h"

// Функция выводит кнопку "старт" в запись.
void DrawStartButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/start.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 50);
	window.draw(buttonSprite);
}

// Функция выводит кнопку "настройки" в запись.
void DrawSettingsButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/settings.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 242);

	window.draw(buttonSprite);
}

// Функция выводит кнопку "выйти" в запись.
void DrawLeaveButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/leave.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 434);

	window.draw(buttonSprite);
}

// Функция выводит кнопку "авторы" в запись.
void DrawAuthorsButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/authors.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(1012, 508);

	window.draw(buttonSprite);
}

// На экран выводится селектор количества чего-то (раундов/ботов) со смещением на x и y пикселей от верхнего левого угла экрана.
void DrawSelector(sf::RenderWindow& window, int x, int y) {

	// На экран выводится стрелка для уменьшения числа раундов.
	sf::Texture leftArrowTexture;
	leftArrowTexture.loadFromFile("../../../images/left_arrow.png");
	sf::Sprite leftArrowSprite(leftArrowTexture);
	leftArrowSprite.setPosition(x, y);
	window.draw(leftArrowSprite);

	// На экран выводится панель счетчика раундов.
	sf::Texture selectCountTexture;
	selectCountTexture.loadFromFile("../../../images/select_count.png");
	sf::Sprite selectCountSprite(selectCountTexture);
	selectCountSprite.setPosition(x + 50, y);
	window.draw(selectCountSprite);

	// На экран выводится стрелка для увеличения количества раундов.
	sf::Texture rightArrowTexture;
	rightArrowTexture.loadFromFile("../../../images/right_arrow.png");
	sf::Sprite rightArrowSprite(rightArrowTexture);
	rightArrowSprite.setPosition(x + 200, y);
	window.draw(rightArrowSprite);
}

// Функция выводит на экран количество раундов.
void DrawNumberOfRounds(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfRounds()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(345, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит на экран количество ботов.
void DrawNumberOfBots(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	sf::Text numberOfRoundsText(std::to_string(gameInfo.GetNumberOfBots()), consolas, 24);
	numberOfRoundsText.setFillColor(sf::Color::White);
	numberOfRoundsText.setPosition(796, 128);
	window.draw(numberOfRoundsText);
}

// Функция выводит на размер карты.
void DrawMapSize(sf::RenderWindow& window, GameInfo& gameInfo) {
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	sf::Text mapSizeText(gameInfo.GetMapSize(), consolas, 24);
	mapSizeText.setFillColor(sf::Color::White);
	mapSizeText.setPosition(541, 252);
	window.draw(mapSizeText);
}

// Функция выводит кнопку "играть" в запись.
void DrawPlayButton(sf::RenderWindow& window) {
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("../../../images/play.png");
	sf::Sprite buttonSprite(buttonTexture);
	buttonSprite.setPosition(426, 388);
	window.draw(buttonSprite);
}

// На экран выводится заголовок счетчика раундов.
void DrawRoundsHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/rounds_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(276, 70);
	window.draw(returnButtonSprite);
}

// На экран выводится заголовок счетчика ботов.
void DrawBotsHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/bots_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(726, 70);
	window.draw(returnButtonSprite);
}

// На экран выводится заголовок выбора карты.
void DrawMapHeader(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/map_header.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(501, 194);
	window.draw(returnButtonSprite);
}

void DrawReturnArrow(sf::RenderWindow& window) {
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/return_arrow.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(10, 10);
	window.draw(returnButtonSprite);
}

// Функция выводит на экран выводится змейка-талисман.
void DrawPythonTalisman(sf::RenderWindow& window) {
	/*Создадим объект типа image и будем выгружать его в оконное приложение
	  Важно создавать объект, т.к. есть свойства, которые не всегда найдутся в текстуре.
	  К примеру маска цветов - можем игнорировать какие либо цвета объекта*/
	sf::Image pythonImage;
	pythonImage.loadFromFile("../../../images/pngwing.com.png");

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

	// В запись заносится кнопка "старт".
	DrawStartButton(window);

	// В запись заносится кнопка "настройки".
	DrawSettingsButton(window);

	// В запись заносится кнопка "выйти".
	DrawLeaveButton(window);

	// В запись заносится кнопка "авторы".
	DrawAuthorsButton(window);
}

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window, GameInfo& gameInfo) {

	// На экран выводится стрелка возвращения назад.
	DrawReturnArrow(window);

	// На экран выводится селектор раундов.
	DrawSelector(window, 226, 120);
	DrawNumberOfRounds(window, gameInfo);
	DrawRoundsHeader(window);

	// На экран выводится селектор ботов.
	DrawSelector(window, 676, 120);
	DrawNumberOfBots(window, gameInfo);
	DrawBotsHeader(window);

	// На экран выводится размер карты.
	DrawSelector(window, 451, 244);
	DrawMapSize(window, gameInfo);
	DrawMapHeader(window);

	// На экран выводится кнопка "играть".
	DrawPlayButton(window);
}
