#include "../include/event.hpp"

// Construtor de Evento.
// Cria um evento associado a uma corrida e um instante de tempo.
Event::Event(double ts, EventType et, Ride* r, int index) {
    this->timestamp = ts;
    this->type = et;
    this->ride = r;
    this->stopIndex = index;
}

// Getters
double Event::getTimestamp() const {
    return this->timestamp;
}

EventType Event::getType() const {
    return this->type;
}

Ride* Event::getRide() const {
    return this->ride;
}

int Event::getIndex() const {
    return this->stopIndex;
}