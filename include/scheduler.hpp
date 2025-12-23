#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.hpp"
class Scheduler {
    private:
    // Estrutura de Dados do Heap
    Event** heapArray;
    int capacity;
    int currentSize;

    // Restaura a propriedade do MinHeap "subindo" um elemento.
    // Chamado após uma inserção no final do vetor. Troca o elemento com seu pai enquanto ele for menor que o pai.
    void siftUp(int index);

    // Restaura a propriedade do MinHeap "descendo" um elemento.
    // Chamado após a remoção da raiz. Troca o elemento com o menor de seus filhos enquanto ele for maior que algum filho.
    void siftDown(int index);

    // Troca dois eventos de posição no vetor.
    void swap(int indexA, int indexB);

    // Getters
    int getParentIndex(int i) { return (i - 1) / 2; }
    int getLeftChildIndex(int i) { return (2 * i) + 1; }
    int getRightChildIndex(int i) { return (2 * i) + 2; }

    public:
    // Construtor do Escalonador.
    // Aloca o array dinâmico para armazenar os eventos.
    Scheduler(int maxCapacity);
    
    // Destrutor do Escalonador.
    // Libera a memória de todos os eventos pendentes e do próprio array.
    ~Scheduler();

    // Insere um novo evento na fila de prioridade.
    // Adiciona o evento ao final e executa siftUp para manter a ordenação temporal.
    void insert(Event* e);

    // Remove e retorna o próximo evento a ocorrer.
    // O "próximo" é sempre o evento com o menor timestamp (raiz do MinHeap).
    // Após remover, reorganiza o heap com siftDown.
    Event* removeNext();
};

#endif