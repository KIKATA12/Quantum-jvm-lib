#include "Qubit.h"
#include <utility>
#include <cmath>
/** 
a qubit state is:
∣𝜓⟩=𝛼∣0⟩+𝛽∣1⟩
where 
  + 𝛼,𝛽∈𝐶 (complex numbers)
  + ∣𝛼∣²+∣𝛽∣²=1(normalization)
**/
Qubit::Qubit() : alpha (1.0, 0.0), beta(0.0, 0.0), active(true) {}
//normalization
void Qubit::normalize() {
  double norm = std::sqrt(std::norm(alpha) + std::norm(beta))
  if(norm > 0){
    alpha /= norm;
    beta /= norm;
}
}
//initialize
void Qubit::initialize (int state){
  if (state == 0) {
    alpha = {1.0, 0.0};
    beta = {0.0, 0.0};
  } else {
    alpha = {0.0, 0.0};
    beta = {1.0, 0.0}; 
  }    
}
//measuring should collapse to 0 / 1
int Qubit::measure() {
  double p0 = std::norm(alpha);
  double randVal = (double)rand() / RAND_MAX;
  if (randVal < p0 ) {
    initialize(0);
    return 0;
  } else {
    initialize(1);
    return 1;
  }
}
//Reset
void Qubit::reset() { initialize(0); }
void Qubit::free() { active = false; } //free memory (simulator abstraction)
void Qubit::release() {active = false; } // free memory, keep amplitudes
//get amplitudes
std::pair<std::complex<double>, std::complex<double>>Qubit::getState() {
return {alpha, beta};
}

