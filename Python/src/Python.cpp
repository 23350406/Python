////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "pythonUpdate.h"

int main()
{
	
	// Откроем окно для вывода
	sf::RenderWindow window(sf::VideoMode(1152, 648), "Python");

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

	// Из файла считывается шрифт Consolas.
	sf::Font consolas;
	consolas.loadFromFile("../../../fonts/Consolas.ttf");

	// Создается массив имен игроков.
	sf::Text* playersNames = new sf::Text[2];
	playersNames[0] = sf::Text("frozzzen", consolas, 14);
	playersNames[0].setFillColor(sf::Color::Cyan);
	playersNames[1] = sf::Text("Sonador", consolas, 14);
	playersNames[1].setFillColor(sf::Color::Green);

	// Создается игровой интерфейс.
	Layout scene;
	scene.SetPlayers(2, playersNames);

	/* Тест для многораундовой игры.
	   Задается номер раунда для демонстарции интерфейса многопользовательской игры.*/
	scene.SetCurrentRound(4);
	scene.SetNumberOfRounds(7);

	/* Тест для однораундовой игры.
	   Количество раундов выставляется на 0.*/
	   /*scene.SetNumberOfRounds(0);*/

	   // Задаются очки игроков.
	unsigned* scores = new unsigned[2];
	scores[0] = 2;
	scores[1] = 3;
	scene.SetScores(scores);

	std::string currentWindowName = "MainMenu";

	// Постоянное обновление картинки
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Экран закрашивается черным.
		window.clear(sf::Color::Black);
		// scene.draw(window);

		if (currentWindowName == "MainMenu") {

			// В вывод на экран заносится главное меню.
			DrawMainMenuWindow(window);

			// Если пользователь нажал кнопку мыши.
			if (event.type == sf::Event::MouseButtonPressed) {

				// И это ЛКМ.
				if (event.mouseButton.button == sf::Mouse::Left) {

					// Пользователь нажал ЛКМ на кнопку "START" -> переход на страницу настроек старта игры.
					if (event.mouseButton.x >= 426 && event.mouseButton.x <= 726 && event.mouseButton.y >= 50 && event.mouseButton.y <= 210) {
						currentWindowName = "StartGame";
					}
				}
			}
		}

		if (currentWindowName == "StartGame") {

			// В вывод на экран заносится экран выбора настроек старта игры.
			DrawStartGameWindow(window);

			// Если пользователь нажал кнопку мыши.
			if (event.type == sf::Event::MouseButtonPressed) {

				// И это ЛКМ.
				if (event.mouseButton.button == sf::Mouse::Left) {

					// Пользователь нажал ЛКМ на кнопку "START" -> переход на страницу настроек старта игры.
					if (event.mouseButton.x >= 10 && event.mouseButton.x <= 90 && event.mouseButton.y >= 10 && event.mouseButton.y <= 70) {
						currentWindowName = "MainMenu";
					}
				}
			}
		}

		// В вывод на экран заносится змейка-талисман.
		window.draw(pythonSprite);

		// Записанное в вывод показывается пользователю.
		window.display();
	}

	return 0;
}
