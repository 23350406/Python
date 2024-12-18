#include "GameInfo.h"

bool Player::Check_isPlayer() { return this->_isPlayer; }

string Player::GetUsername() { return this->_username; }

string Player::GetColor() { return this->_color; }

char Player::GetMove(string move)
{
    if(move == "up")    {return this->_up;}
    if(move == "down")  {return this->_down;}
    if(move == "left")  {return this->_left;}
    if(move == "right") {return this->_right;}
    // return '0';
}

void Player::SetUsername(string username) { this->_username = username; }

void Player::SetColor(string color) { this->_color = color; }

void Player::SetMove(string moveName, char letterMove) //movename - какое движение будет перезаписываться, letterMove - кнопка записи
{
    this->_up    = (moveName == "up") ? letterMove : this->_up;
    this->_down  = (moveName == "down") ? letterMove : this->_down;
    this->_left  = (moveName == "left") ? letterMove : this->_left;
    this->_right = (moveName == "right") ? letterMove : this->_right;
}