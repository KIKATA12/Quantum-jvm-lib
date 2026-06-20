#include "QubitRegistry.h"

int QubitRegistry::createQubit(int state) {
  auto q = std::make_unique<Qubit>();
  //call Qubit::initialize()
  q -> initialize(state); 
  int id = nextId++;
  qubits[id] = std::move(q);
  return id;
}
Qubit* QubitRegistry::getQubit(int id) {
  auto it = qubits.find(id);
  if (it != qubits.end()){
    return it->second.get();
  }
  return nullptr;
}
int QubitRegistry::measureQubit(int id) {
  Qubit* q = getQubit(id);
  //calls Qubit::Measure()
  if (q) return q->measure();
  throw std::runtime_error("Qubit not found");
}
void QubitRegistry::resetQubit(int id){
  Qubit* q = getQubit(id);
  //calls Qubit::reset()
  if (q) q->reset();
}
void QubitRegistry::releaseQubit(int id){
  //remove Qubit from registry
  qubits.erase(id);
}
void QubitRegistry::printQubit(int id) {
  Qubit* q = getQubit(id);
  if (q) {
    auto [alpha, beta] = q->getState();
    std::cout << "Qubit" << id << ":" << alpha << "|0> + " << beta << "|1>" << std::endl;
  }
}
