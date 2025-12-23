# Simulador de Despacho de Corridas (Ride-Sharing Dispatch)

Este projeto implementa um sistema de despacho de transporte por aplicativo focado em *ride-sharing* (corridas compartilhadas), desenvolvido para a empresa fictícia "Cabe Aí" (CabAI). O sistema utiliza **Simulação de Eventos Discretos (SED)** para processar solicitações em tempo real e otimizar a ocupação da frota.

## Sobre o Projeto

O objetivo do algoritmo é decidir se uma demanda de transporte deve ser atendida individualmente ou agrupada com outras em uma única rota, visando reduzir custos e maximizar a eficiência. O simulador gerencia a frota ao longo do tempo, respeitando restrições rígidas de janelas temporais, capacidade do veículo e eficiência da rota.

Desenvolvido em **C++** como parte da disciplina de Estruturas de Dados (UFMG), o projeto destaca-se pelo **gerenciamento manual de memória** e implementação de estruturas de dados fundamentais sem o uso de contêineres automáticos da STL.

## Funcionalidades Principais

* **Algoritmo de Emparelhamento (Matching):** Agrupa passageiros baseado em proximidade geográfica (origem/destino), janelas de tempo ($\delta$) e eficiência mínima ($\lambda$).
* **Simulação de Eventos Discretos (SED):** Utiliza um relógio lógico e uma fila de prioridade para processar eventos de embarque e desembarque cronologicamente.
* **Gerenciamento de Memória:** Alocação dinâmica manual de vetores e objetos, com tratamento rigoroso para evitar vazamentos (*memory leaks*).
* **Estruturas de Dados Personalizadas:** Implementação própria de *MinHeap* (para o escalonador) e vetores dinâmicos.

## Método e Arquitetura

O sistema opera em duas fases distintas:

1.  **Despacho (Matching):**
    * Itera sobre as demandas ordenadas temporalmente.
    * Verifica candidatos a compartilhamento (carona) que satisfaçam: Capacidade $\le \eta$, Atraso $\le \delta$ e Eficiência $\ge \lambda$.
    * Define rotas seguindo a lógica FIFO (First-In, First-Out) para coletas e entregas.

2.  **Motor de Simulação:**
    * Controlado por um **Escalonador (Scheduler)** baseado em *MinHeap*.
    * Processa eventos (coleta/entrega/deslocamento) e atualiza o estado da frota e estatísticas finais.

## Análise de Complexidade

| Componente | Complexidade de Tempo | Descrição |
| :--- | :--- | :--- |
| **Algoritmo de Despacho** | $O(N^2)$ | Dominado por laços aninhados que comparam cada demanda com candidatos futuros. |
| **Motor de Simulação** | $O(N \log N)$ | Processamento de $2N$ eventos, onde cada operação no Heap custa $O(\log N)$. |
| **Espaço (Memória)** | $O(N)$ | Crescimento linear para armazenar demandas, corridas e eventos no Heap. |

*Nota: $N$ é o número de demandas de entrada.*
