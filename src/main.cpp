#include <iostream>
#include <cmath>
#include <iomanip>
#include <new>
#include <limits>
#include "../include/ride.hpp"
#include "../include/scheduler.hpp"
#include "../include/utils.hpp"


int main() {

    int eta; 
    double gama, delta, alfa, beta, lambda;
    int numdemandas;

    // Validação de Entrada
    // Verifica se a leitura dos parâmetros globais foi bem-sucedida.
    if (!(std::cin >> eta >> gama >> delta >> alfa >> beta >> lambda)) {
        std::cerr << "Erro crítico: Falha na leitura dos parâmetros de configuração." << std::endl;
        return 1;
    }

    if (!(std::cin >> numdemandas)) {
        std::cerr << "Erro crítico: Falha na leitura do número de demandas." << std::endl;
        return 1;
    }

    if (numdemandas < 0) {
        std::cerr << "Erro lógico: Número negativo de demandas." << std::endl;
        return 1;
    }

    // Bloco Try-Catch para capturar erros de alocação dinâmica (std::bad_alloc).
    try {
        // Cria vetor de ponteiros para armazenar todas as demandas.
        Demand** listOfAllDemands = new Demand*[numdemandas];
        
        for (int i = 0; i < numdemandas; i++) {
            int id;
            double requestTime;
            double ox, oy, dx, dy;
            
            if (!(std::cin >> id >> requestTime >> ox >> oy >> dx >> dy)) {
                std::cerr << "Erro de formatação na demanda índice " << i << std::endl;
                return 1;
            }
            
            Point origin(ox, oy);
            Point destination(dx, dy);
            listOfAllDemands[i] = new Demand(id, requestTime, origin, destination);
        }

        // Inicialização das estruturas principais: Vetor de Corridas e Escalonador.
        Ride** R = new Ride*[numdemandas];
        int rideCount = 0;
        Scheduler* scheduler = new Scheduler(numdemandas * 2);

        // Estratégia Gulosa: Para cada demanda não atendida, tenta criar uma nova corrida.
        for (int i = 0; i < numdemandas; i++) {
            Demand* c0 = listOfAllDemands[i];
            
            // Se a demanda já foi alocada em uma iteração anterior, ignora.
            if (c0->getStatus() == DemandStatus::COMBINED || c0->getStatus() == DemandStatus::INDIVIDUAL) {
                continue;
            }

            // Inicia uma nova corrida com c0.
            Ride* newRide = new Ride(eta);
            newRide->addDemand(c0);
            c0->setStatus(DemandStatus::INDIVIDUAL);

            // Loop interno: Busca candidatos a carona nas demandas subsequentes.
            for (int j = i + 1; j < numdemandas; j++) {
                Demand* cj = listOfAllDemands[j];

                // Filtro 1: Demanda disponível?
                if (cj->getStatus() != DemandStatus::REQUESTED) continue;

                // Filtro 2: Capacidade do veículo atingida?
                if (newRide->getDemandCount() == eta) break;

                // Filtro 3: Janela de tempo (Delta) excedida?
                if (cj->getRequestTime() - c0->getRequestTime() >= delta) break;

                // Filtro 4: Proximidade Geográfica (Conjuntiva).
                bool failedTheCheck = false;
                for (int k = 0; k < newRide->getDemandCount(); k++){
                    Demand* existingDemand = newRide->getDemands()[k];

                    Point origin_cj = cj->getOrigin();
                    Point origin_existing = existingDemand->getOrigin();
                    double distOrigin = calculateDistance(origin_cj.getX(), origin_cj.getY(), origin_existing.getX(), origin_existing.getY());
                    
                    Point dest_cj = cj->getDestination();
                    Point dest_existing = existingDemand->getDestination();
                    double distDest = calculateDistance(dest_cj.getX(), dest_cj.getY(), dest_existing.getX(), dest_existing.getY());

                    if (distOrigin > alfa || distDest > beta) {
                        failedTheCheck = true;
                        break;
                    }
                }
                if (failedTheCheck) break; // Se falhou com qualquer um, descarta o candidato e encerra busca para esta corrida.

                // Filtro 5: Eficiência Mínima (Lambda).
                double efficiency = calculateEfficiency(newRide, cj);
                if (efficiency <= lambda) break;

                // SUCESSO: Candidato aceito. Adiciona à corrida.
                newRide->addDemand(cj);
                cj->setStatus(DemandStatus::COMBINED);
                c0->setStatus(DemandStatus::COMBINED);
            }

            // Construção da Rota Física
            // Criação temporária das Paradas para gerar os Segmentos.
            Stop** stops = new Stop*[newRide->getDemandCount() * 2];

            // Adiciona Paradas de Embarque (Pickup)
            for (int k = 0; k < newRide->getDemandCount(); k++) {
                Demand* currentDemand = newRide->getDemands()[k];
                stops[k] = new Stop(currentDemand->getOrigin(), StopType::PICKUP, currentDemand);
            }

            // Adiciona Paradas de Desembarque (Dropoff)
            for (int k = 0; k < newRide->getDemandCount(); k++) {
                Demand* currentDemand = newRide->getDemands()[k];
                int index = k + newRide->getDemandCount();
                stops[index] = new Stop(currentDemand->getDestination(), StopType::DROPOFF, currentDemand);
            }

            // Cria os Segmentos conectando as paradas sequencialmente
            for (int k = 0; k < (newRide->getDemandCount() * 2) - 1; k++) {
                Stop* startStop = stops[k];
                Stop* endStop = stops[k+1];

                Point start = startStop->getCoordinates();
                Point end = endStop->getCoordinates();

                double distance = calculateDistance(start.getX(), start.getY(), end.getX(), end.getY());
                double time = distance / gama;

                // Acumula distância total da corrida
                newRide->setTotalDistance(newRide->getTotalDistance() + distance);

                // Define o tipo do segmento
                SegmentType typeSegment;
                if (startStop->getType() == StopType::PICKUP && endStop->getType() == StopType::PICKUP) {
                    typeSegment = SegmentType::COLLECTION;
                } else if (startStop->getType() == StopType::PICKUP && endStop->getType() == StopType::DROPOFF) {
                    typeSegment = SegmentType::DISPLACEMENT;
                } else {
                    typeSegment = SegmentType::DELIVERY;
                }

                newRide->addSegment(new Segment(startStop, endStop, time, distance, typeSegment));
            }

            // Limpeza do array auxiliar de stops (os objetos Stop agora pertencem à Ride)
            delete[] stops;
            
            // Agendamento do Evento Inicial: Chegada para o primeiro embarque.
            double startTime = c0->getRequestTime();
            Event* firstEvent = new Event(startTime, EventType::PICKUP_ARRIVAL, newRide, 0);
            scheduler->insert(firstEvent);

            // Armazena a corrida finalizada na lista global.
            R[rideCount] = newRide;
            rideCount++;
        }

        // SIMULAÇÃO (Motor de Eventos Discretos)
        double simulationClock = 0.0;

        while(true) {
            // Remove o próximo evento cronológico da fila de prioridade.
            Event* currentEvent = scheduler->removeNext();
            if (currentEvent == nullptr) break;

            // Avança o relógio lógico.
            simulationClock = currentEvent->getTimestamp();
            Ride* ride = currentEvent->getRide();
            int stopIndex = currentEvent->getIndex();

            // Verifica se é o último evento da corrida (chegada no último destino).
            if (stopIndex == (ride->getDemandCount() * 2) - 1) {
                // Corrida Concluída: Gera a saída formatada.
                std::cout << std::fixed << std::setprecision(2);
                std::cout << simulationClock << " ";
                std::cout << ride->getTotalDistance() << " ";
                
                int numStops = ride->getDemandCount() * 2;
                std::cout << numStops;

                // Imprime coordenadas de todas as paradas (início dos segmentos)
                for (int k = 0; k < ride->getSegmentCount(); k++) {
                    Point p = ride->getSegments()[k]->getStartStop()->getCoordinates();
                    std::cout << " " << p.getX() << " " << p.getY();
                }

                // Imprime a coordenada final (fim do último segmento)
                Point p_final = ride->getSegments()[ride->getSegmentCount() - 1]->getEndStop()->getCoordinates();
                std::cout << " " << p_final.getX() << " " << p_final.getY();
                std::cout << std::endl;

            } else {
                // Corrida em andamento: Agenda a chegada na próxima parada.
                Segment* currentSegment = ride->getSegments()[stopIndex];

                // Calcula tempo futuro: Agora + tempo do trecho atual.
                double newTimestamp = simulationClock + currentSegment->getTime();
                int nextStopIndex = stopIndex + 1;

                // Define o tipo do próximo evento baseado na próxima parada.
                Stop* nextStop = currentSegment->getEndStop();
                EventType newType = (nextStop->getType() == StopType::PICKUP) ? EventType::PICKUP_ARRIVAL : EventType::DROPOFF_ARRIVAL;

                // Insere novo evento no Escalonador.
                Event* nextEvent = new Event(newTimestamp, newType, ride, nextStopIndex);
                scheduler->insert(nextEvent);
            }

            // Libera memória do evento processado.
            delete currentEvent;
        }

        // LIMPEZA GERAL
        delete scheduler;

        for (int i = 0; i < rideCount; i++) {
            delete R[i]; // Destrutor da Ride limpa seus Segments e Stops.
        }
        for (int i = 0; i < numdemandas; i++) {
            delete listOfAllDemands[i];
        }

        delete[] R;
        delete[] listOfAllDemands;

    } catch (const std::bad_alloc& e) {
        std::cerr << "Erro fatal: Falha de alocação de memória (" << e.what() << ")" << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Erro não tratado: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}