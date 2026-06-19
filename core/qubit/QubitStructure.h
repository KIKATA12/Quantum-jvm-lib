#pragma once

#include <complex>
#include <utility>

class QubitStructure {
private:
std::complex<double> alpha;
std::complex<double> beta;
bool active;
void normalize();

public:
QubitStructure();
void initialize(int state);
int measure();
void reset();
void free();
void release();
std::pair<std::complex<double>, std::complex<double>> getState();
};
