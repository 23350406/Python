// pythonUpdate.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

// Библиотека, чтобы узнавать размер экрана пользователя.
#include <windows.h>


// Класс, отвечающий за визуализацию игрового интерфейса.
class Layout
{
private:

	// Количество игроков.
	unsigned _numberOfPlayers;

	// Имена игроков.
	sf::Text* _playersNames;

	// Номер текущего раунда.
	unsigned _currentRound;

	// Количество раундов в многораундовой игре.
	unsigned _numberOfRounds;

	// Очки игроков.
	unsigned* _scores;

	// Размер поля. Поле квадратное, поэтому цифра одна
	unsigned _fieldSize;
public:

	// Конструктор по умолчанию.
	Layout()
	{
		_playersNames = nullptr;
		_scores = nullptr;
	}

	// Функция задает игроков.
	void SetPlayers(unsigned numberOfPlayers, sf::Text* playersNames)
	{
		_numberOfPlayers = numberOfPlayers;
		if (_playersNames != nullptr) {
			delete[] _playersNames;
		}
		_playersNames = new sf::Text[_numberOfPlayers];
		for (int i = 0; i < _numberOfPlayers; ++i)
		{
			_playersNames[i] = playersNames[i];
		}
	}

	// Функция задает номер текущего раунда для многораундовой игры.
	void SetCurrentRound(unsigned currentRound)
	{
		_currentRound = currentRound;
	}

	// Функция задает количество раундов в многораундовой игре.
	void SetNumberOfRounds(unsigned numberOfRounds)
	{
		_numberOfRounds = numberOfRounds;
	}

	// Функция задает массив очков игроков.
	void SetScores(unsigned* scores)
	{
		if (_scores != nullptr) {
			delete[] _scores;
		}
		_scores = new unsigned[_numberOfPlayers];
		for (int i = 0; i < _numberOfPlayers; ++i)
		{
			_scores[i] = scores[i];
		}
	}

	// Функция задаёт размер поля
	void SetFieldSize(int size)
	{
		_fieldSize = size;
	}

	// Функция задает количество игроков.
	unsigned GetNumberOfPlayers()
	{
		return _numberOfPlayers;
	}

	// Функция задает имена игроков.
	sf::Text* GetPlayersNames()
	{
		return _playersNames;
	}

	// Функция задает номер текущего раунда для многораундовой игры.
	unsigned GetCurrentRound()
	{
		return _currentRound;
	}

	// Функция задает количество раундов в многораундовой игре.
	unsigned GetNumberOfRounds()
	{
		return _numberOfRounds;
	}

	// Функция задает массив очков игроков.
	unsigned* GetScores()
	{
		return _scores;
	}

	unsigned GetFieldSize()
	{
		return _fieldSize;
	}

	// Метод, выводящий игровой интерфейс на экран.
	void draw(sf::RenderWindow& window)
	{

		// Окно заполняется черным цветом.
		sf::RectangleShape background(sf::Vector2f(900, 600));
		background.setFillColor(sf::Color::Black);
		window.draw(background);

		// По двум точкам создается прямая, разделяющая игровое и информационное поля.
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0, 550)),
			sf::Vertex(sf::Vector2f(900, 550))
		};
		line[0].color = sf::Color::Yellow;
		line[1].color = sf::Color::Yellow;
		window.draw(line, 2, sf::Lines);

		// Из файла считывается шрифт Consolas.
		sf::Font consolas;
		consolas.loadFromFile("../../../fonts/Consolas.ttf");

		// На будущее создается переменная, куда будет записываться титульная надпись для игроков.
		sf::Text titleText("", consolas, 16);

		// Выводится информация о игроках.
		for (int i = 0; i < GetNumberOfPlayers(); ++i)
		{

			// Создается титульная надпись для игрока.
			std::string title;
			if (_numberOfPlayers != 1) {
				title = "Player" + std::to_string(i + 1) + ":";
			}
			else {
				title = "Player:";
			}

			// Задается стиль титульной надписи.
			titleText.setString(title);
			titleText.setFillColor(_playersNames[i].getFillColor());
			titleText.setPosition(20 + i * 160, 555);

			// Титульная надпись выводится на экран.
			window.draw(titleText);

			// Для каждого игрока создается и выводится "Score:".
			sf::Text scoreTitle("Score:", consolas, 16);
			scoreTitle.setFillColor(_playersNames[i].getFillColor());
			scoreTitle.setPosition(100 + i * 160, 555);
			window.draw(scoreTitle);

			// На экран выводится имя игрока.
			_playersNames[i].setPosition(20 + i * 160, 575);
			window.draw(_playersNames[i]);

			// Для каждого игрока создается и выводится надпись, отвечающая за его очки.
			sf::Text scoreText(std::to_string(_scores[i]), consolas, 14);
			scoreText.setFillColor(_playersNames[i].getFillColor());
			scoreText.setPosition(100 + i * 160, 575);
			window.draw(scoreText);
		}

		// Выводится номер раунда, если игра многораундовая.
		if (_numberOfRounds > 0) {

			// Формируется строка вида "Номер текущего раунда / Количество всех раундов"
			std::string rounds = std::to_string(_currentRound) + " / " + std::to_string(_numberOfRounds);

			// Текст, выводимый на экран создается и выводится.
			sf::Text roundText(rounds, consolas, 14);
			roundText.setFillColor(sf::Color::Yellow);
			roundText.setPosition(820, 575);
			window.draw(roundText);

			// Формируется и выводится на экран надпись "Раунд:".
			sf::Text roundTitle("Round:", consolas, 16);
			roundTitle.setFillColor(sf::Color::Yellow);
			roundTitle.setPosition(820, 555);
			window.draw(roundTitle);
		}

		// Задаётся размер поля
		SetFieldSize(400);

		// Добавим отрисовку маленьких квадратиков
		unsigned lengthSquare = GetFieldSize();
		for (int i = 0; i < lengthSquare; i += 20) {
			for (int j = 0; j < lengthSquare; j += 20) {
				sf::RectangleShape littleSquare(sf::Vector2f(20, 20));
				littleSquare.setFillColor(sf::Color(44, 44, 44)); // Черно-серый
				littleSquare.setPosition(250 + i, 80 + j);

				// Добавим цвет рамкии её толщину
				littleSquare.setOutlineColor(sf::Color(15, 69, 7)); // Тёмно-зелёный
				littleSquare.setOutlineThickness(1);
				window.draw(littleSquare);
			}
		}
	}
};

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
	returnButtonTexture.loadFromFile("../../../images/rounds_header.png");
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

// Функция выводит экран настроек старта игры.
void DrawStartGameWindow(sf::RenderWindow& window) {

	// На экран выводится стрелка возвращения назад.
	sf::Texture returnButtonTexture;
	returnButtonTexture.loadFromFile("../../../images/return_arrow.png");
	sf::Sprite returnButtonSprite(returnButtonTexture);
	returnButtonSprite.setPosition(10, 10);
	window.draw(returnButtonSprite);

	// На экран выводится селектор раундов.
	DrawSelector(window, 226, 120);
	DrawRoundsHeader(window);

	// На экран выводится селектор ботов.
	DrawSelector(window, 676, 120);
	DrawBotsHeader(window);

	// На экран выводится селектор ботов.
	DrawSelector(window, 451, 244);
	DrawMapHeader(window);

	DrawPlayButton(window);
}

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
