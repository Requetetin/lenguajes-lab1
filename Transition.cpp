#include "Headers/Transition.h"

Transition::Transition() = default;

Transition::Transition(int src, int dest, char sym) {
  this->source = src;
  this->destiny = dest;
  this->symbol = sym;
  this->symbolEquivalent = sym + 0;
}

void Transition::print() {
  cout << "\"" << source << "\": {\"" << symbol << "\": \"" << destiny << "\"},\n";
}

void Transition::printDot() {
  cout << source << " -> " << destiny << " [label = \"" << symbol << "\"];\n";
}