#include "../include/segment.hpp"

// Construtor de Segmento.
// Inicializa o objeto com as referências das paradas e os dados calculados.
Segment::Segment(Stop* ss, Stop* es, double t, double d, SegmentType ty) {
    this->startStop = ss;
    this->endStop = es;
    this->time = t;
    this->distance = d;
    this->type = ty;
}

// Getters
Stop* Segment::getStartStop() const {
    return this->startStop;
}

Stop* Segment::getEndStop() const {
    return this->endStop;
}

double Segment::getTime() const {
    return this->time;
}

double Segment::getDistance() const {
    return this->distance;
}

SegmentType Segment::getType() const {
    return this->type;
}