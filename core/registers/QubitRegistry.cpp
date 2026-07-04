#include "QubitRegistry.h"
#include "../gates/GateWrapper.h"
#include <stdexcept>

int QubitRegistry::createQubit(int state) {
  auto q = std::make_unique<Qubit>();
  q->initialize(state);
  int id = nextId++;
  qubits[id] = std::move(q);
  return id;
}

Qubit* QubitRegistry::getQubit(int id) {
  auto it = qubits.find(id);
  if (it != qubits.end()) {
    return it->second.get();
  }
  return nullptr;
}

int QubitRegistry::measureQubit(int id) {
  Qubit* q = getQubit(id);
  if (q) return q->measure();
  throw std::runtime_error("Qubit not found");
}

void QubitRegistry::resetQubit(int id){
  Qubit* q = getQubit(id);
  if (q) q->reset();
}

void QubitRegistry::releaseQubit(int id){
  qubits.erase(id);
}

void QubitRegistry::printQubit(int id) {
  Qubit* q = getQubit(id);
  if (q) {
    auto [alpha, beta] = q->getState();
    std::cout << "Qubit" << id << ":" << alpha << "|0> + " << beta << "|1>" << std::endl;
  }
}

void QubitRegistry::superimpose(int id, const std::string& gate, double params) {
  Qubit* q = getQubit(id);
  if (!q) {
    throw std::runtime_error("Qubit not found");
  }

  GateWrapper::applyGate(*q, gate, params);
}
