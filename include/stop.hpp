#ifndef STOP_H
#define STOP_H

#include "point.hpp"

class Demand; // Forward declaration

// Define o tipo de ação realizada na parada.
enum class StopType {
    PICKUP, // Embarque de passageiro (início da viagem individual).
    DROPOFF // Desembarque de passageiro (fim da viagem individual).
};

class Stop {
    private:
    Point coordinates;
    StopType type;
    Demand* demand;

    public:
    // Construtor de Parada.
    // Inicializa a parada vinculando o local, o tipo de ação e o passageiro.
    Stop(Point p, StopType t, Demand* d);

    // Getters.
    Point getCoordinates() const;
    StopType getType() const;
    Demand* getDemand() const;
};

#endif