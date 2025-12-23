#ifndef EVENT_H
#define EVENT_H

// Define os estados possíveis de um Evento durante a simulação.
enum class EventType { 
    PICKUP_ARRIVAL, // O veículo chegou ao ponto de embarque (Coleta).
    DROPOFF_ARRIVAL // O veículo chegou ao ponto de desembarque (Entrega).
};

class Ride; // Forward declaration.

class Event {
    private:
    double timestamp;
    EventType type;
    Ride* ride;
    int stopIndex;
    
    public:
    // Construtor de Evento.
    // Cria um evento associado a uma corrida e um instante de tempo.
    Event(double ts, EventType et, Ride* r, int index);
    
    // Getters.
    double getTimestamp() const;
    EventType getType() const;
    Ride* getRide() const;
    int getIndex() const;
};

#endif