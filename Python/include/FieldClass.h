#include "functionsFullProject.h"

int Field::GetHeight() { return _height; }

int Field::GetWidth() { return _width; }

vector<vector<Cell>> Field::GetField() { return _field; }

// vector<Player> Field::GetTeam() { return _players; }

int Field::GetCountPlayers() { return _countPlayers; }

int Field::GetCountBots() { return _countBots; }

void Field::SetHeight(int height) { _height = height; }

void Field::SetWidth(int width) { _width = width; }

void Field::SetLine(vector<vector<Cell>> field) { _field = field;}

void Field::SetTeam(vector<Player> players) { _players = players; }

void Field::SetCountBots(int countBots) { _countBots = countBots; }

void Field::SetCountPlayers(int countPlayers) { _countPlayers = countPlayers; };

void Field::InitializeFrom(int height, int width, int countPlayers, int countBots) {
    _height = height;
    _width = width;

    vector<int> randomValuesX = GenerateRandomValues(height);
    vector<int> randomValuesY = GenerateRandomValues(height);

    int countRandomElement = 0;
    // Инициализация карты
    for (int i = 0; i < height; ++i) {
        vector<Cell> row;

        for (int j = 0; j < width; ++j) {
            Cell temp;
            if (find(randomValuesX.begin(), randomValuesX.end(), i) != randomValuesX.end() && find(randomValuesY.begin(), randomValuesY.end(), j) != randomValuesY.end()) {
                if (countRandomElement == 0) {
                    sf::Image headImage;
                    headImage.loadFromFile("../images/headSnake.png");
				    temp.SetImage(headImage);
                    temp.SetIsBusy(true);

                    _snake.SetxHead(i);
                    _snake.SetyHead(j);
                    _snake.SetxTail(i);
                    _snake.SetyTail(j);

                    ++countRandomElement;
                    row.insert(row.begin() + j, temp);
                    continue;
                }

                if (countRandomElement == 4) {
                    sf::Image headImage;
                    headImage.loadFromFile("../images/klukva.png");
				    temp.SetImage(headImage);
                    ++countRandomElement;
                    row.insert(row.begin() + j, temp);
                    continue;
                }

                sf::Image headImage;
                headImage.loadFromFile("../images/stena.png");
				temp.SetImage(headImage);
                temp.SetIsBusy(true);
                ++countRandomElement;
			}
            row.insert(row.begin() + j, temp);
        }

        _field.insert(_field.begin() + i, row);
    }

    _countBots = countBots;
    _countPlayers = countPlayers;

    Player player(sf::Color::Magenta, "bro", true);
    _players.push_back(player);
}

Field::Field(int height, int width, int countPlayers, int countBots) {
      InitializeFrom(height, width, countPlayers, countBots);
}
