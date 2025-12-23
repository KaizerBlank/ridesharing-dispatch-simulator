# Ride-Sharing Dispatch Simulator

This project implements a dispatch system for an app-based ride-sharing service, developed for the fictitious company "CabAI". The system employs **Discrete Event Simulation (DES)** to process real-time requests and optimize fleet occupancy.

## About the Project

The core algorithm decides whether a transport request should be served individually or grouped with others into a shared route (ride-sharing), aiming to reduce operational costs and maximize efficiency. The simulator manages the fleet over time, strictly adhering to constraints such as time windows, vehicle capacity, and route efficiency.

Developed in **C++** as part of the Data Structures course at the Federal University of Minas Gerais (UFMG), this project stands out for its **manual memory management** and the implementation of fundamental data structures without relying on automatic STL containers.

## Key Features

* **Matching Algorithm:** Groups passengers based on geographical proximity (origin/destination), time windows ($\delta$), and minimum efficiency ($\lambda$).
* **Discrete Event Simulation (DES):** Utilizes a logical clock and a priority queue to process pickup and drop-off events chronologically.
* **Memory Management:** Manual dynamic allocation of vectors and objects, with rigorous handling to prevent memory leaks.
* **Custom Data Structures:** Implementation of a MinHeap (for the scheduler) and dynamic arrays from scratch.

## Method and Architecture

The system operates in two distinct phases:

### 1. Dispatch (Matching)
* Iterates through temporally sorted demands.
* Checks for potential ride-sharing candidates satisfying:
    * Capacity $\le \eta$
    * Delay $\le \delta$
    * Efficiency $\ge \lambda$
* Constructs routes following a FIFO (First-In, First-Out) logic for pickups and drop-offs.

### 2. Simulation Engine
* Controlled by a **Scheduler** based on a **MinHeap**.
* Processes events (pickup/drop-off/movement) and updates fleet state and final statistics.

## Complexity Analysis

| Component | Time Complexity | Description |
| :--- | :--- | :--- |
| **Dispatch Algorithm** | $O(N^2)$ | Dominated by nested loops comparing each demand with future candidates. |
| **Simulation Engine** | $O(N \log N)$ | Processing $2N$ events, where each Heap operation costs $O(\log N)$. |
| **Space (Memory)** | $O(N)$ | Linear growth to store demands, rides, and events in the Heap. |

> **Note:** $N$ is the number of input demands.
