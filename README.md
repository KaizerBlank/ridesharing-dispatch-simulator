# Ride-Sharing Dispatch Simulator

This project implements a dispatch system for an app-based ride-sharing service, developed for the fictitious company "CabAI". The system employs **Discrete Event Simulation (DES)** to process real-time requests and optimize fleet occupancy.

## 📋 About the Project

The core algorithm decides whether a transport request should be served individually or grouped with others into a shared route (ride-sharing), aiming to reduce operational costs and maximize efficiency. The simulator manages the fleet over time, strictly adhering to constraints such as time windows, vehicle capacity, and route efficiency.

Developed in **C++** as part of the Data Structures course at the Federal University of Minas Gerais (UFMG), this project stands out for its **manual memory management** and the implementation of fundamental data structures without relying on automatic STL containers.

## 🚀 Key Features

* [cite_start]**Matching Algorithm:** Groups passengers based on geographical proximity (origin/destination), time windows ($\delta$), and minimum efficiency ($\lambda$)[cite: 203, 258].
* [cite_start]**Discrete Event Simulation (DES):** Utilizes a logical clock and a priority queue to process pickup and drop-off events chronologically[cite: 204, 267].
* [cite_start]**Memory Management:** Manual dynamic allocation of vectors and objects, with rigorous handling to prevent **memory leaks**[cite: 333].
* [cite_start]**Custom Data Structures:** Implementation of a **MinHeap** (for the scheduler) and dynamic arrays from scratch[cite: 237, 309].

## 🛠️ Method and Architecture

The system operates in two distinct phases:

1.  **Dispatch (Matching):**
    * Iterates through temporally sorted demands.
    * [cite_start]Checks for potential ride-sharing candidates satisfying: Capacity $\le \eta$, Delay $\le \delta$, and Efficiency $\ge \lambda$[cite: 254].
    * [cite_start]Constructs routes following a FIFO (First-In, First-Out) logic for pickups and drop-offs[cite: 262].

2.  **Simulation Engine:**
    * Controlled by a **Scheduler** based on a *MinHeap*.
    * [cite_start]Processes events (pickup/drop-off/movement) and updates fleet state and final statistics[cite: 266, 270].

## 📊 Complexity Analysis

| Component | Time Complexity | Description |
| :--- | :--- | :--- |
| **Dispatch Algorithm** | $O(N^2)$ | [cite_start]Dominated by nested loops comparing each demand with future candidates[cite: 287, 302]. |
| **Simulation Engine** | $O(N \log N)$ | [cite_start]Processing $2N$ events, where each Heap operation costs $O(\log N)$[cite: 296]. |
| **Space (Memory)** | $O(N)$ | [cite_start]Linear growth to store demands, rides, and events in the Heap[cite: 316]. |

*Note: N is the number of input demands.*
