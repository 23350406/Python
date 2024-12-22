#include "functionsFullProject.h"

sf::Image Cell::GetImage()  { return _imageCell; }

void Cell::SetImage(sf::Image type) {_imageCell = type;}

Cell::Cell() {
    _imageCell.loadFromFile("../images/cell.png");
    _isBusy = false;
}

Cell::Cell(sf::Image img, bool isBusy) {
    _imageCell = img;
    _isBusy = isBusy;
}

bool Cell::GetIsBusy() {
    return _isBusy;
}

void Cell::SetIsBusy(bool busy) {
    _isBusy = busy;
}
