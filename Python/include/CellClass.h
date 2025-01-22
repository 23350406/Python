#include "functionsFullProject.h"

void Cell::SetImage(const sf::Image &img) { _imageCell = img; }

sf::Image Cell::GetImage() { return _imageCell; }

Cell::Cell() {
  _type = CellType::EMPTY;
  _isBusy = false;
}

void Cell::SetType(CellType type) { _type = type; }

CellType Cell::GetType() const { return _type; }

Cell::Cell(sf::Image img, bool isBusy, CellType type) {
  _imageCell = img;
  _isBusy = isBusy;
  _type = type;
}

bool Cell::GetIsBusy() { return _isBusy; }

void Cell::SetIsBusy(bool busy) { _isBusy = busy; }
