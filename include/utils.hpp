#ifndef UTILS_H
#define UTILS_H

// Foward declarations.
class Ride;
class Demand;

// Calcula a distância Euclidiana entre dois pontos no plano 2D.
double calculateDistance(double p1x, double p1y, double p2x, double p2y);

//Calcula a eficiência de adicionar um passageiro candidato a uma corrida existente.
// A eficiência é a razão entre a soma das distâncias individuais e a distância da rota compartilhada.
double calculateEfficiency(const Ride* currentRide, const Demand* candidateDemand);

#endif