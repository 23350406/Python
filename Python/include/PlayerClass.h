#include "functionsFullProject.h"

Player::Player(sf::Color color, string username, bool isPlayer) {
  _color = color;
  _username = username;
  _isPlayer = isPlayer;
}

bool Player::Check_isPlayer() { return _isPlayer; }

string Player::GetUsername() { return _username; }

sf::Color Player::GetColor() { return _color; }

char Player::GetMove(string moveName) {
  if (moveName == "up") {
    return _up;
  }
  if (moveName == "down") {
    return _down;
  }
  if (moveName == "left") {
    return _left;
  }
  if (moveName == "right") {
    return _right;
  }
  return '0';
}

void Player::SetUsername(string username) { _username = username; }

void Player::SetColor(int r, int g, int b) { _color = sf::Color(r, g, b); }

void Player::SetMove(
    string moveName,
    char letterMove) // movename - какое движение будет перезаписываться,
                     // letterMove - кнопка записи
{
  _up = (moveName == "up") ? letterMove : _up;
  _down = (moveName == "down") ? letterMove : _down;
  _left = (moveName == "left") ? letterMove : _left;
  _right = (moveName == "right") ? letterMove : _right;
}
