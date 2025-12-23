#include "../include/scheduler.hpp"
#include <cassert>
#include <iostream>

// Construtor do Escalonador.
// Aloca o array dinâmico para armazenar os eventos.
Scheduler::Scheduler(int maxCapacity) {
    this->capacity = maxCapacity;
    this->currentSize = 0;
    this->heapArray = new Event*[this->capacity];
}

// Destrutor do Escalonador.
// Libera a memória de todos os eventos pendentes e do próprio array.
Scheduler::~Scheduler() {
    for (int i = 0; i < this->currentSize; i++)
    {
        delete this->heapArray[i];
    }
    delete[] this->heapArray;
}

// Troca dois eventos de posição no vetor.
void Scheduler::swap(int indexA, int indexB) {
    Event* temp = this->heapArray[indexA];
    this->heapArray[indexA] = this->heapArray[indexB];
    this->heapArray[indexB] = temp;
}

// Restaura a propriedade do MinHeap "subindo" um elemento.
void Scheduler::siftUp(int index) {
    assert(index >= 0 && index < this->currentSize); // Validação de premissa

    while (index > 0 && this->heapArray[index]->getTimestamp() < this->heapArray[getParentIndex(index)]->getTimestamp()) {
        swap(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

// Adiciona ao final e executa siftUp. Inclui checagem de capacidade.
void Scheduler::insert(Event* e) {
    if (this->currentSize == this->capacity) {
        std::cerr << "Scheduler cheio, Capacidade máxima (" << this->capacity << ") atingida. Evento descartado." << std::endl;
        return; 
    }

    // Validação de premissa: Ponteiro não deve ser nulo
    assert(e != nullptr); 

    this->heapArray[this->currentSize] = e;
    this->currentSize++;

    siftUp(this->currentSize - 1);
}

// Restaura a propriedade do MinHeap "descendo" um elemento.
void Scheduler::siftDown(int index) {
    int leftChild = getLeftChildIndex(index);
    int rightChild = getRightChildIndex(index);
    int smallestChild = index;

    if (leftChild < this->currentSize && this->heapArray[leftChild]->getTimestamp() < this->heapArray[smallestChild]->getTimestamp()) {
        smallestChild = leftChild;
    }

    if (rightChild < this->currentSize && this->heapArray[rightChild]->getTimestamp() < this->heapArray[smallestChild]->getTimestamp()) {
        smallestChild = rightChild;
    }

    if (smallestChild != index) {
        swap(index, smallestChild);

        siftDown(smallestChild);
    }
}

// Remove e retorna o próximo evento a ocorrer (menor timestamp).
Event* Scheduler::removeNext() {
    if (this->currentSize == 0) {
        return nullptr;
    }

    Event* eventToReturn = this->heapArray[0];
    
    // Validação de integridade
    assert(eventToReturn != nullptr);

    this->heapArray[0] = this->heapArray[this->currentSize - 1];
    this->currentSize--;

    if (this->currentSize > 0) {
        siftDown(0);
    }

    return eventToReturn;
}
