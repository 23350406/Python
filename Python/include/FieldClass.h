#include "GameInfo.h"

int Field::GetHeight() { return this->_height; }

int Field::GetWidth() { return this->_width; }

vector<Cell*> Field::GetLine() { return this->_line; }

vector<Player> Field::GetTeam() { return this->_team; }

void Field::SetHeight(int height) { this->_height = height; }

void Field::SetWidth(int width) { this->_width = width; }

void Field::SetLine(vector<Cell*> line) { this->_line = line;}

void Field::SetTeam(vector<Player> team) { this->_team = team; }
