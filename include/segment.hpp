#ifndef SEGMENT_H
#define SEGMENT_H

#include "stop.hpp"

// Define a natureza do deslocamento entre duas paradas.
enum class SegmentType{
    COLLECTION, // Trecho entre dois embarques (coletando passageiros).
    DELIVERY, // Trecho entre dois desembarques (entregando passageiros).
    DISPLACEMENT // Trecho de transição (do último embarque para o primeiro desembarque).
};

class Segment {
    private:
    Stop* startStop;
    Stop* endStop;
    double time; 
    double distance; 
    SegmentType type; 

    public:
    // Construtor de Segmento.
    // Inicializa o objeto com as referências das paradas e os dados calculados.
    Segment(Stop* ss, Stop* es, double t, double d, SegmentType ty);
    
    // Destrutor
    // A responsabilidade de limpar a memória das Paradas (Stops) é exclusivamente da classe Ride.
    // Isso evita o erro de "double free" (liberação dupla de memória).
    ~Segment() = default; 

    // Getters
    Stop* getStartStop() const;
    Stop* getEndStop() const;
    double getTime() const;
    double getDistance() const;
    SegmentType getType() const;
};

#endif