# Simulador de Despacho de Corridas (Ride-Sharing Dispatch)

Este projeto implementa um sistema de despacho de transporte por aplicativo focado em *ride-sharing* (corridas compartilhadas), desenvolvido para a empresa fictícia "Cabe Aí" (CabAI). [cite_start]O sistema utiliza **Simulação de Eventos Discretos (SED)** para processar solicitações em tempo real e otimizar a ocupação da frota[cite: 197, 198].

## Sobre o Projeto

[cite_start]O objetivo do algoritmo é decidir se uma demanda de transporte deve ser atendida individualmente ou agrupada com outras em uma única rota, visando reduzir custos e maximizar a eficiência[cite: 199]. [cite_start]O simulador gerencia a frota ao longo do tempo, respeitando restrições rígidas de janelas temporais, capacidade do veículo e eficiência da rota[cite: 200, 203].

[cite_start]Desenvolvido em **C++** como parte da disciplina de Estruturas de Dados (UFMG), o projeto destaca-se pelo **gerenciamento manual de memória** e implementação de estruturas de dados fundamentais sem o uso de contêineres automáticos da STL[cite: 323, 474].

## Funcionalidades Principais

* [cite_start]**Algoritmo de Emparelhamento (Matching):** Agrupa passageiros baseado em proximidade geográfica (origem/destino), janelas de tempo ($\delta$) e eficiência mínima ($\lambda$)[cite: 203, 258].
* [cite_start]**Simulação de Eventos Discretos (SED):** Utiliza um relógio lógico e uma fila de prioridade para processar eventos de embarque e desembarque cronologicamente[cite: 204, 267].
* [cite_start]**Gerenciamento de Memória:** Alocação dinâmica manual de vetores e objetos, com tratamento rigoroso para evitar vazamentos (*memory leaks*)[cite: 333].
* [cite_start]**Estruturas de Dados Personalizadas:** Implementação própria de *MinHeap* (para o escalonador) e vetores dinâmicos[cite: 237, 309].

## Método e Arquitetura

[cite_start]O sistema opera em duas fases distintas[cite: 249]:

1.  **Despacho (Matching):**
    * Itera sobre as demandas ordenadas temporalmente.
    * [cite_start]Verifica candidatos a compartilhamento (carona) que satisfaçam: Capacidade $\le \eta$, Atraso $\le \delta$ e Eficiência $\ge \lambda$[cite: 254].
    * [cite_start]Define rotas seguindo a lógica FIFO (First-In, First-Out) para coletas e entregas[cite: 262].

2.  **Motor de Simulação:**
    * Controlado por um **Escalonador (Scheduler)** baseado em *MinHeap*.
    * [cite_start]Processa eventos (coleta/entrega/deslocamento) e atualiza o estado da frota e estatísticas finais[cite: 266, 270].

## Análise de Complexidade

| Componente | Complexidade de Tempo | Descrição |
| :--- | :--- | :--- |
| **Algoritmo de Despacho** | $O(N^2)$ | [cite_start]Dominado por laços aninhados que comparam cada demanda com candidatos futuros[cite: 287]. |
| **Motor de Simulação** | $O(N \log N)$ | [cite_start]Processamento de $2N$ eventos, onde cada operação no Heap custa $O(\log N)$[cite: 296]. |
| **Espaço (Memória)** | $O(N)$ | [cite_start]Crescimento linear para armazenar demandas, corridas e eventos no Heap[cite: 316]. |

*Nota: $N$ é o número de demandas de entrada.*
