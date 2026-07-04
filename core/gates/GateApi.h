#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double real;
    double imag;
} ComplexValue;

typedef struct {
    ComplexValue alpha;
    ComplexValue beta;
} QubitC;

void pauliX(QubitC* qubit);
void pauliY(QubitC* qubit);
void pauliZ(QubitC* qubit);

void rotationX(QubitC* qubit, double theta);
void rotationY(QubitC* qubit, double theta);
void rotationZ(QubitC* qubit, double theta);

#ifdef __cplusplus
}
#endif
