#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

typedef struct 
{
    double complex alpha;
    double complex beta;
}QubitC;
 
// Pauli-X gate: flips the state of a qubit
void pauliX(QubitC* qubit){
    double complex temp = qubit->alpha;
    qubit->alpha = qubit->beta;
    qubit->beta = temp;
}

// Pauli-Y gate: applies a phase flip 0f factor i
void pauliY(QubitC* qubit){
    double complex temp0 = qubit->alpha;
    double complex temp1 = qubit->beta;
    qubit->alpha = -I * temp1;
    qubit->beta = I * temp0;
}

// Pauli-Z gate: applies a phase flip of |1> 
void pauliZ(QubitC* qubit){
    qubit->beta = -qubit->beta;
}