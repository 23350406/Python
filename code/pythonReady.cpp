////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

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
	// Колчиество раундов в многораундовой игре.
	unsigned _numberOfRounds;
	// Очки игроков.
	unsigned* _scores;
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
		consolas.loadFromFile("fonts/Consolas.ttf");
		// На будущее создается переменная, куда будет записываться титульная надпись для игроков.
		sf::Text titleText("", consolas, 16);

		// Выводится информация о игроках.
		for (int i = 0; i < _numberOfPlayers; ++i)
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
	}
};

int main()
{
	// Откроем окно для вывода
	sf::RenderWindow window(sf::VideoMode(900, 600), "Python");

	/*Создадим объект типа image и будем выгружать его в оконное приложение
	  Важно создавать объект, т.к. есть свойства, которые не всегда найдутся в текстуре.
	  К примеру маска цветов - можем игнорировать какие либо цвета объекта*/
	sf::Image pythonImage;
	pythonImage.loadFromFile("images/pngwing.com.png");

	// Текстура и есть изображение. Можно не использовать Image (НО НЕЛЬЗЯ!!)
	sf::Texture pythonTexture;
	pythonTexture.loadFromImage(pythonImage);

	sf::Sprite pythonSprite;
	pythonSprite.setTexture(pythonTexture);
	pythonSprite.setPosition(420, 25);


	// Из файла считывается шрифт Consolas.
	sf::Font consolas;
	consolas.loadFromFile("fonts/Consolas.ttf");

	// Создается массив имен игроков.
	sf::Text* playersNames = new sf::Text[2];
	playersNames[0] = sf::Text("frozzzen", consolas, 14);
	playersNames[0].setFillColor(sf::Color::Cyan);
	playersNames[1] = sf::Text("Sonador", consolas, 14);
	playersNames[1].setFillColor(sf::Color::Green);

	// Создается игровой интерфейс.
	Layout scene;
	scene.SetPlayers(2, playersNames);

	// Тест для многораундовой игры.
	// Задается номер раунда для демонстарции интерфейса многопользовательской игры.
	// scene.SetCurrentRound(4);
	// scene.SetNumberOfRounds(7);
	// 
	// Тест для однораундовой игры.
	// Количество раундов выставляется на 0.
	scene.SetNumberOfRounds(0);
	// 
	// Задаются очки игроков.
	unsigned* scores = new unsigned[2];
	scores[0] = 2;
	scores[1] = 3;
	scene.SetScores(scores);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(pythonSprite);
		scene.draw(window);
		window.display();
	}

	return 0;
}
