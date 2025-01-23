#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include "functionsFullProject.h"

// Функция создает первого игрока.
PlayerInfo CreateFirstPlayer() {
  PlayerInfo info;
  info.SetName("P1");
  info.SetUpKey(sf::Keyboard::W);
  info.SetDownKey(sf::Keyboard::S);
  info.SetLeftKey(sf::Keyboard::A);
  info.SetRightKey(sf::Keyboard::D);
  info.SetColor(sf::Color(255, 0, 0));
  return info;
}

// Функция создает второго игрока.
PlayerInfo CreateSecondPlayer() {
  PlayerInfo info;
  info.SetName("P2");
  info.SetUpKey(sf::Keyboard::Up);
  info.SetDownKey(sf::Keyboard::Down);
  info.SetLeftKey(sf::Keyboard::Left);
  info.SetRightKey(sf::Keyboard::Right);
  info.SetColor(sf::Color(0, 255, 234));
  return info;
}

// Функция задает имя игрока.
void PlayerInfo::SetName(std::string newName) { _playerName = newName; }

// Функция возвращает имя игрока.
std::string PlayerInfo::GetName() { return _playerName; }

// Функция задает значение клавиши для движения вверх.
void PlayerInfo::SetUpKey(sf::Keyboard::Key newUp) { _up = newUp; }

void PlayerInfo::LoadFromFile(std::ifstream &file) {
  std::string line;
  while (std::getline(file, line)) {
    std::string key;

    // Извлечение ключа
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
      key = line.substr(0, pos);
    } else {
      key = line; // Если пробелов нет, вся строка - это ключ
    }

    // Извлечение значения
    if (key == "PlayerName") {
      _playerName = line.substr(pos + 1);
    } else if (key == "Up") {
      int keyValue = std::stoi(line.substr(pos + 1));
      _up = static_cast<sf::Keyboard::Key>(keyValue);
    } else if (key == "Left") {
      int keyValue = std::stoi(line.substr(pos + 1));
      _left = static_cast<sf::Keyboard::Key>(keyValue);
    } else if (key == "Right") {
      int keyValue = std::stoi(line.substr(pos + 1));
      _right = static_cast<sf::Keyboard::Key>(keyValue);
    } else if (key == "Down") {
      int keyValue = std::stoi(line.substr(pos + 1));
      _down = static_cast<sf::Keyboard::Key>(keyValue);
    } else if (key == "Color") {
      std::string colorValues = line.substr(pos + 1);
      size_t firstSpace = colorValues.find(' ');
      size_t secondSpace = colorValues.find(' ', firstSpace + 1);

      int r = std::stoi(colorValues.substr(0, firstSpace));
      int g = std::stoi(
          colorValues.substr(firstSpace + 1, secondSpace - firstSpace - 1));
      int b = std::stoi(colorValues.substr(secondSpace + 1));

      _playerColor = sf::Color(r, g, b);
    }
  }
}

void PlayerInfo::SaveToFile(std::ofstream &file) const {
  file << "PlayerName " << _playerName << "\n";
  file << "Up " << static_cast<int>(_up) << "\n";
  file << "Left " << static_cast<int>(_left) << "\n";
  file << "Right " << static_cast<int>(_right) << "\n";
  file << "Down " << static_cast<int>(_down) << "\n";
  file << "Color " << (int)_playerColor.r << " " << (int)_playerColor.g << " "
       << (int)_playerColor.b << "\n";
}

// Функция возвращает значение клавиши для движения вверх.
sf::Keyboard::Key PlayerInfo::GetUpKey() { return _up; }

// Функция задает значение клавиши для движения вниз.
void PlayerInfo::SetDownKey(sf::Keyboard::Key newDown) { _down = newDown; }

// Функция возвращает значение клавиши для движения вниз.
sf::Keyboard::Key PlayerInfo::GetDownKey() { return _down; }

// Функция задает значение клавиши для движения вправо.
void PlayerInfo::SetRightKey(sf::Keyboard::Key newRight) { _right = newRight; }

// Функция возвращает значение клавиши для движения вправо.
sf::Keyboard::Key PlayerInfo::GetRightKey() { return _right; }

// Функция задает значение клавиши для движения влево.
void PlayerInfo::SetLeftKey(sf::Keyboard::Key newLeft) { _left = newLeft; }

// Функция возвращает значение клавиши для движения влево.
sf::Keyboard::Key PlayerInfo::GetLeftKey() { return _left; }

// Функция задает значение цвета игрока.
void PlayerInfo::SetColor(sf::Color newColor) { _playerColor = newColor; }

// Функция возвращает значение цвета игрока.
sf::Color PlayerInfo::GetColor() { return _playerColor; }

#endif // PLAYERINFO_HPP
