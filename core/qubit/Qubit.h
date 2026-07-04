#pragma once

#include <complex>
#include <utility>

class Qubit {
private:
std::complex<double> alpha;
std::complex<double> beta;
bool active;
void normalize();

public:
Qubit();
void initialize(int state);
void setState(const std::complex<double>& newAlpha, const std::complex<double>& newBeta);
int measure();
void reset();
void free();
void release();
std::pair<std::complex<double>, std::complex<double>> getState();
};
