#pragma once

#include "../qubit/Qubit.h"
#include <string>

class GateWrapper {
public:
  static void applyGate(Qubit& qubit, const std::string& gateName, double params = 0.0);
};
