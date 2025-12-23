#include "../include/demand.hpp"

// Construtor de Demanda.
// Inicializa uma nova demanda com os dados brutos e define o status inicial como REQUESTED.
Demand::Demand(int id, double rt, Point o, Point d) 
    : origin(o), destination(d) {
    this->id = id;
    this->requestTime = rt;
    this->status = DemandStatus::REQUESTED;
    this->associatedRide = nullptr;
}

// Getters
int Demand::getId() const {
    return this->id;
}

double Demand::getRequestTime() const {
    return this->requestTime;
}

Point Demand::getOrigin() const {
    return this->origin;
}

Point Demand::getDestination() const {
    return this->destination;
}

DemandStatus Demand::getStatus() const {
    return this->status;
}

Ride* Demand::getRide() const {
    return this->associatedRide;
}

// Setters
void Demand::setStatus(DemandStatus newStatus) {
    this->status = newStatus;
}

void Demand::setAssociatedRide(Ride* ride) {
    this->associatedRide = ride;
}