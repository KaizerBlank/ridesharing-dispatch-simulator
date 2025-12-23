#include "../include/point.hpp"

// Construtor de Point, inicializa um ponto com coordenadas cartesianas (x, y).
Point::Point(double px, double py) {
    this->x = px;
    this->y = py;
}

// Getters
double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}