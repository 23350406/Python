////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

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


		sf::Font consolas;
		consolas.loadFromFile("fonts/Consolas.ttf");
		// На будущее создается переменная, куда будет записываться титульная надпись для игроков.
		sf::Text titleText("", consolas, 14);

		// Выводятся имена всех игроков.
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
			titleText.setPosition(20 + i * 80, 560);

			// Титульная надпись выводится на экран.
			window.draw(titleText);

			// На экран выводится имя игрока.
			_playersNames[i].setPosition(20 + i * 80, 573);
			window.draw(_playersNames[i]);
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
