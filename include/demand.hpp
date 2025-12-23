#ifndef DEMAND_H
#define DEMAND_H

#include "point.hpp"

// Forward declaration
class Ride;

// Define os estados possíveis de uma demanda durante a simulação.
enum class DemandStatus {
    REQUESTED, // Demanda lida no arquivo mas nao foi processada.
    INDIVIDUAL, // Demanda foi alocada em um corrida, inicialmente individual.
    COMBINED, // Demanda foi alocada com sucesso em uma corrida compartilhada.
    COMPLETED // A corrida associada a essa demanda foi finalizada com sucesso.
};

class Demand {
    private:
    int id;
    double requestTime;
    Point origin;
    Point destination;
    DemandStatus status;
    Ride* associatedRide;

    public:
    // Construtor de Demanda.
    // Inicializa uma nova demanda com os dados brutos e define o status inicial como REQUESTED.
    Demand(int id, double rt, Point o, Point d);

    // Getters
    int getId() const;
    double getRequestTime() const;
    Point getOrigin() const;
    Point getDestination() const;
    DemandStatus getStatus() const;
    Ride* getRide() const;

    // Setters
    void setStatus(DemandStatus newStatus);
    void setAssociatedRide(Ride* ride);
};

#endif