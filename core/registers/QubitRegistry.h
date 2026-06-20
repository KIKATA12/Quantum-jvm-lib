#pragma once
#include "../qubit/Qubit.h"
#include <map>
#include <memory>
#include <iostream>

class QubitRegistry {
private:
  std::map<int, std::unique_ptr<Qubit>> qubits;
  int nextId = 0;
public:
  int createQubit(int state = 0);
  Qubit* getQubit(int id);
  int measureQubit(int id);
  void resetQubit(int id);
  void releaseQubit(int id);
  void printQubit(int id);
};
