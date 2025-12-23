#include "../include/utils.hpp"
#include "../include/ride.hpp"
#include "../include/demand.hpp"
#include <cmath>


//Calcula a distância Euclidiana entre dois pontos no plano 2D.
double calculateDistance(double p1x, double p1y, double p2x, double p2y) {
    double x = p2x - p1x;
    double y = p2y - p1y;
    return std::sqrt((x * x) + (y * y));
}

// Calcula a eficiência de adicionar um passageiro candidato a uma corrida existente.
//A eficiência é a razão entre a soma das distâncias individuais e a distância da rota compartilhada.
double calculateEfficiency(const Ride* currentRide, const Demand* candidateDemand) {
    // Numerador (Soma das distâncias individuais)
    double somaIndividuais = 0.0;

    for (int k = 0; k < currentRide->getDemandCount(); k++) {
        Demand* existingDemand = currentRide->getDemands()[k];
        Point origin = existingDemand->getOrigin();
        Point dest = existingDemand->getDestination();
        somaIndividuais += calculateDistance(origin.getX(), origin.getY(), dest.getX(), dest.getY());
    }

    Point origin_cj = candidateDemand->getOrigin();
    Point dest_cj = candidateDemand->getDestination();
    somaIndividuais += calculateDistance(origin_cj.getX(), origin_cj.getY(), dest_cj.getX(), dest_cj.getY());

    // Denominador (Distância real da rota compartilhada)
    double somaCompartilhada = 0.0;

    // Rota de Coletas (Origem -> Origem -> ...)
    Point currentPoint = currentRide->getDemands()[0]->getOrigin();
    
    for (int k = 1; k < currentRide->getDemandCount(); k++) {
        Point nextPoint = currentRide->getDemands()[k]->getOrigin();
        somaCompartilhada += calculateDistance(currentPoint.getX(), currentPoint.getY(), nextPoint.getX(), nextPoint.getY());
        currentPoint = nextPoint;
    }

    Point candidateOrigin = candidateDemand->getOrigin();
    somaCompartilhada += calculateDistance(currentPoint.getX(), currentPoint.getY(), candidateOrigin.getX(), candidateOrigin.getY());
    currentPoint = candidateOrigin;

    // Deslocamento (Última Origem -> Primeiro Destino)
    Point firstDestination = currentRide->getDemands()[0]->getDestination();
    somaCompartilhada += calculateDistance(currentPoint.getX(), currentPoint.getY(), firstDestination.getX(), firstDestination.getY());
    currentPoint = firstDestination;

    // Rota de Entregas (Destino -> Destino -> ...)
    for (int k = 1; k < currentRide->getDemandCount(); k++) {
        Point nextPoint = currentRide->getDemands()[k]->getDestination();
        somaCompartilhada += calculateDistance(currentPoint.getX(), currentPoint.getY(), nextPoint.getX(), nextPoint.getY());
        currentPoint = nextPoint;
    }

    Point candidateDestination = candidateDemand->getDestination();
    somaCompartilhada += calculateDistance(currentPoint.getX(), currentPoint.getY(), candidateDestination.getX(), candidateDestination.getY());

    // Prevenção de divisão por zero
    if (somaCompartilhada == 0.0) {
        return 0.0;
    }
    
    return somaIndividuais / somaCompartilhada;
}