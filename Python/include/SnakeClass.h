#include "functionsFullProject.h"

int Snake::GetxHead() { return this->_head_x; }

int Snake::GetyHead() { return this->_head_y; }

int Snake::GetxTail() { return this->_tail_x; }

int Snake::GetyTail() { return this->_tail_y; }

string Snake::GetDirection() { return this->_direction; }

void Snake::SetxHead(int head_x){ this->_head_x = head_x;}

void Snake::SetyHead(int head_y){ this->_head_y = head_y;}

void Snake::SetxTail(int tail_x){ this->_tail_x = tail_x;}

void Snake::SetyTail(int tail_y){ this->_tail_y = tail_y;}

void Snake::SetDirection(string direction) { this->_direction = direction; }
