#include "functionsFullProject.h"

int Field::GetHeight() { return this->_height; }

int Field::GetWidth() { return this->_width; }

vector<Cell*> Field::GetField() { return this->_field; }

vector<Player> Field::GetTeam() { return this->_players; }

void Field::SetHeight(int height) { this->_height = height; }

void Field::SetWidth(int width) { this->_width = width; }

void Field::SetLine(vector<Cell*> field) { this->_field = field;}

void Field::SetTeam(vector<Player> players) { this->_players = players; }
