#include "../include/ride.hpp"
#include <iostream>

// Construtor de Corrida.
// Aloca dinamicamente os vetores de demandas e segmentos.
Ride::Ride(int maxCapacity) {
    this->demandCapacity = maxCapacity;
    this->demands = new Demand*[this->demandCapacity];
    this->demandCount = 0;

    this->segmentCapacity = (2 * maxCapacity) - 1;
    this->segments = new Segment*[this->segmentCapacity];
    this->segmentCount = 0;

    this->totalDuration = 0.0;
    this->totalDistance = 0.0;
    this->efficiency = 0.0;
}

// Destrutor
// Libera a memória das paradas, segmentos e vetores auxiliares.
Ride::~Ride() {
    // 1. Deleta as paradas de INÍCIO de cada trecho
    for(int i = 0; i < this->segmentCount; i++) {
        delete this->segments[i]->getStartStop();
    }

    // 2. Deleta a parada de FIM do último trecho
    if (this->segmentCount > 0) {
        delete this->segments[this->segmentCount - 1]->getEndStop();
    }

    // 3. Deleta os objetos Segmento
    for(int i = 0; i < this->segmentCount; i++) {
        delete this->segments[i];
    }

    // 4. Libera os arrays dinâmicos
    delete[] this->segments;
    delete[] this->demands;
}

// Getters

Demand** Ride::getDemands() const {
    return this->demands;
}

Segment** Ride::getSegments() const {
    return this->segments;
}

double Ride::getTotalDuration() const {
    return this->totalDuration;
}

double Ride::getTotalDistance() const {
    return this->totalDistance;
}

double Ride::getEfficiency() const {
    return this->efficiency;
}

int Ride::getDemandCount() const {
    return this->demandCount;
}

int Ride::getDemandCapacity() const {
    return this->demandCapacity;
}

int Ride::getSegmentCount() const {
    return this->segmentCount;
}

int Ride::getSegmentCapacity() const {
    return this->segmentCapacity;
}

// Setters

void Ride::setTotalDistance(double d) {
    this->totalDistance = d;
}

// Adiciona um trecho ao final da lista de Segmentos.
void Ride::addSegment(Segment* s) {
    if(this->segmentCount < this->segmentCapacity) {
        this->segments[this->segmentCount] = s;
        this->segmentCount++;
    } else {
        // Prevenção de Overflow
        std::cerr << "Tentativa de adicionar Segmento em Corrida cheia. Capacidade: " << this->segmentCapacity << std::endl;
    }
}

// Adiciona uma demanda ao final da lista de Demandas.
void Ride::addDemand(Demand* d) {
    if(this->demandCount < this->demandCapacity) {
        this->demands[this->demandCount] = d;
        this->demandCount++;
    } else {
        // Prevenção de Overflow
        std::cerr << "Tentativa de adicionar Demanda em Corrida cheia. Capacidade: " << this->demandCapacity << std::endl;
    }
}