# QUANTUM-JVM-LIB

## Overview
Quantum JVM Library is a modular quantum computing framework designed for the Java ecosystem, 
with a high‑performance C++ core connected via JNI. 
Inspired by Qiskit, it provides a clean API for building, simulating, 
and experimenting with quantum circuits directly from Java applications.
using Java wrappers and api calls.

## Goal
This is a research and study project. The goal is to understand Quantum
computing technologies, Building and implementing Quantum components including
Qubits, Gates and algorithms in order to apply the knowledge in real life 
as solutions to classical computing shortcomings. 

C++ has been selected to build the library core due to the following 
considerations

### Performance:  
Quantum simulation involves heavy linear algebra (matrix multiplications, tensor products, complex numbers). 
C++ gives you speed and low‑level memory control that Java alone can’t match.

### Numerical Libraries:  
You can leverage existing C++ libraries (like Eigen, Armadillo, or BLAS/LAPACK)
for efficient matrix operations. These are battle‑tested in scientific computing.

### Fine‑grained control:  
Quantum states are vectors of complex amplitudes. C++ lets you manage them directly, 
optimize memory layout, and avoid garbage collection overhead.

### Portability:  
A C++ core can be compiled into native libraries and reused across languages (Java, Python, Rust).
With JNI, Java developers get access without sacrificing speed.

to make this project Unique, Java Bindings (JNI) will be used to make calls
to the C++ functions, In this way we can have the Java community that is not 
served by Qiskit to be the testing platform for Quantum computing and if successful 
later on the project can give insights on how to secure Java Enterprise applications
With Quantum cryptos.

## Milestones and study roadmap
### Milestone 1
+ study Qubits, dirac notation, superposition
+ implement Qubits in Cpp
+ create JNI wrapper for Qubits

### Milestone 2
+ Study Entanglement and basic gates
+ Implement the gates Cpp class
+ Test entaglement with Qubit states
+ Create JNI wrapper for Gates

### Milestone 3
+ Study Quantum circuits and Deutsch-Jozsa algorithm
+ Build circuit class (sequence of gates)
+ implement Deutsch-Jozsa and Berstein vazirani algorithms
+ Expose endpoints to java 

### Milestone 4
+ study grover's search algorithm
+ implement grover algorithm using the circuit class
+ JNI wrapper Grover.run()

### Milestone 5
+ Study the QFT algorithm
+ implement QFT in C++ and integrate into circuit class
+ JNI wrapper QFT.run()

### Milestone 6
+ Study shor's algorithm
+ implement simplified shor in Cpp
+ JNI wrapper Shor.run ()

### Milestone 7
+ Learn the quantum teleportation (register to register) (entaglement + classical communication)
+ implement Teleportation module in C++
+ extend register class to handle entangled pairs
+ create a JNI wrapper
+ teleport a qubit state between registers

### Milestone 8
+ study VQE and QAOA
+ focus on how classical optimization loops interact
+ with quantum circuits
+ implement VQE modules in Cpp (Hamiltonians)
+ add interface for classical optimizers (gradient descents)
+ create JNI wrapper

### Milestone 9
+ Learn Simon'S algorithms (hidden XOR mask problem)
+ Understand Simon's exponential speed up on classical algorithms
+ implement simon module
+ extend circuit to handle oracle functions
+ create JNI wrapper

### Milestone 10
+ Other Physics inspired extenstions.
