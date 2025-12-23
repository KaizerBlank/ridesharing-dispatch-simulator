#ifndef RIDE_H
#define RIDE_H

#include "segment.hpp"
#include "demand.hpp"

class Ride {
    private:
    // Gerenciamento de Demandas
    Demand** demands;
    int demandCapacity;
    int demandCount;

    // Gerenciamento de Rotas
    Segment** segments;
    int segmentCapacity;
    int segmentCount;

    // Estatísticas
    double totalDuration;
    double totalDistance;
    double efficiency;

    public: 
    // Construtor de Corrida.
    // Aloca dinamicamente os vetores de demandas e segmentos.
    Ride(int maxCapacity);

    // Destrutor
    // Libera a memória das paradas, segmentos e vetores auxiliares.
    ~Ride();

    // Getters
    Demand** getDemands() const;
    Segment** getSegments() const;
    
    double getTotalDuration() const;
    double getTotalDistance() const;
    double getEfficiency() const;

    int getDemandCount() const;
    int getDemandCapacity() const;
    int getSegmentCount() const;
    int getSegmentCapacity() const;

    // Setters
    void setTotalDistance(double d);

    // Adiciona um trecho ao final da lista de Segmentos.
    void addSegment(Segment* s);

    // Adiciona uma demanda ao final da lista de Demandas.
    void addDemand(Demand* d);
};

#endif