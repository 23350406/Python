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
void PlayerInfo::SetName(std::string newName) {
    _playerName = newName;
}

// Функция возвращает имя игрока.
std::string PlayerInfo::GetName() {
    return _playerName;
}

// Загрузка и сохранение информации о игроке
void PlayerInfo::LoadFromFile(std::ifstream &inFile) {
    std::getline(inFile, _playerName);
    int up, left, right, down;
    inFile >> up >> left >> right >> down;
    _up = static_cast<sf::Keyboard::Key>(up);
    _left = static_cast<sf::Keyboard::Key>(left);
    _right = static_cast<sf::Keyboard::Key>(right);
    _down = static_cast<sf::Keyboard::Key>(down);
    int r, g, b;
    inFile >> r >> g >> b;
    _playerColor = sf::Color(r, g, b);
    inFile.ignore(); // Игнорируем символ новой строки
}

void PlayerInfo::SaveToFile(std::ofstream &outFile) const {
    outFile << _playerName << std::endl;
    outFile << static_cast<int>(_up) << std::endl;
    outFile << static_cast<int>(_left) << std::endl;
    outFile << static_cast<int>(_right) << std::endl;
    outFile << static_cast<int>(_down) << std::endl;
    outFile << static_cast<int>(_playerColor.r) << " "
            << static_cast<int>(_playerColor.g) << " "
            << static_cast<int>(_playerColor.b) << std::endl;
}

// Функция задает значение клавиши для движения вверх.
void PlayerInfo::SetUpKey(sf::Keyboard::Key newUp) {
    _up = newUp;
}

// Функция возвращает значение клавиши для движения вверх.
sf::Keyboard::Key PlayerInfo::GetUpKey() {
    return _up;
}

// Функция задает значение клавиши для движения вниз.
void PlayerInfo::SetDownKey(sf::Keyboard::Key newDown) {
    _down = newDown;
}

// Функция возвращает значение клавиши для движения вниз.
sf::Keyboard::Key PlayerInfo::GetDownKey() {
    return _down;
}

// Функция задает значение клавиши для движения вправо.
void PlayerInfo::SetRightKey(sf::Keyboard::Key newRight) {
    _right = newRight;
}

// Функция возвращает значение клавиши для движения вправо.
sf::Keyboard::Key PlayerInfo::GetRightKey() {
    return _right;
}

// Функция задает значение клавиши для движения влево.
void PlayerInfo::SetLeftKey(sf::Keyboard::Key newLeft) {
    _left = newLeft;
}

// Функция возвращает значение клавиши для движения влево.
sf::Keyboard::Key PlayerInfo::GetLeftKey() {
    return _left;
}

// Функция задает значение цвета игрока.
void PlayerInfo::SetColor(sf::Color newColor) {
    _playerColor = newColor;
}

// Функция возвращает значение цвета игрока.
sf::Color PlayerInfo::GetColor() {
    return _playerColor;
}

#endif // PLAYERINFO_HPP
