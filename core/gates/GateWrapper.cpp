#include "GateWrapper.h"
#include "GateApi.h"
#include <algorithm>
#include <cctype>
#include <complex>
#include <stdexcept>

void GateWrapper::applyGate(Qubit& qubit, const std::string& gateName, double params) {
  auto [alpha, beta] = qubit.getState();
  QubitC state{};
  state.alpha.real = std::real(alpha);
  state.alpha.imag = std::imag(alpha);
  state.beta.real = std::real(beta);
  state.beta.imag = std::imag(beta);

  std::string normalized = gateName;
  std::transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });

  if (normalized == "x" || normalized == "pauli-x" || normalized == "paulix") {
    pauliX(&state);
  } else if (normalized == "y" || normalized == "pauli-y" || normalized == "pauliy") {
    pauliY(&state);
  } else if (normalized == "z" || normalized == "pauli-z" || normalized == "pauliz") {
    pauliZ(&state);
  } else if (normalized == "rx") {
    rotationX(&state, params);
  } else if (normalized == "ry") {
    rotationY(&state, params);
  } else if (normalized == "rz") {
    rotationZ(&state, params);
  } else {
    throw std::runtime_error("Unsupported gate: " + gateName);
  }

  qubit.setState(
      std::complex<double>(state.alpha.real, state.alpha.imag),
      std::complex<double>(state.beta.real, state.beta.imag));
}
