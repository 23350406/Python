#include "functionsFullProject.h"

bool Player::Check_isPlayer() { return this->_isPlayer; }

string Player::GetUsername() { return this->_username; }

sf::Color Player::GetColor() { return this->_color; }

char Player::GetMove(string moveName)
{
    if(moveName == "up")    {return this->_up;}
    if(moveName == "down")  {return this->_down;}
    if(moveName == "left")  {return this->_left;}
    if(moveName == "right") {return this->_right;}
    return '0';
}

void Player::SetUsername(string username) { this->_username = username; }

void Player::SetColor(int r, int g, int b) {
    _color = sf::Color(r,g,b);
}

void Player::SetMove(string moveName, char letterMove) //movename - какое движение будет перезаписываться, letterMove - кнопка записи
{
    this->_up    = (moveName == "up") ? letterMove : this->_up;
    this->_down  = (moveName == "down") ? letterMove : this->_down;
    this->_left  = (moveName == "left") ? letterMove : this->_left;
    this->_right = (moveName == "right") ? letterMove : this->_right;
}