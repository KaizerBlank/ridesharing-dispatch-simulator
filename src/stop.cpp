#include "../include/stop.hpp"

// Construtor de Parada.
// Inicializa a parada vinculando o local, o tipo de ação e o passageiro.
Stop::Stop(Point p, StopType t, Demand* d) : coordinates(p) {
    this->type = t;
    this->demand = d;
}

// Getters
Point Stop::getCoordinates() const {
    return this->coordinates;
}

StopType Stop::getType() const {
    return this->type;
}

Demand* Stop::getDemand() const {
    return this->demand;
}