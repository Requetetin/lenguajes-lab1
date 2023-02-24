#include "Headers/AFN.h"

AFN::AFN() = default;

AFN::AFN(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions) {
  this->initial = initialState;
  this->states = allStates;
  this->accepted = acceptedStates;
  this->transitions = allTransitions;
  for (Transition &transition : transitions) {
    int transitionSymbol = transition.getSymbolEquiv();
    if (find(this->symbols.begin(), this->symbols.end(), transitionSymbol) != symbols.end()) {
      this->symbols.push_back(transition.getSymbol());
    }
  }
}

void AFN::print() {
  cout << "Initial: " << initial << endl;
  cout << "States: ";
  printVectors(states);
  cout << "Acceptance states: ";
  printVectors(accepted);
  cout << "Transitions: " << endl;
  for (Transition &transition: transitions) {
    transition.print();
  }
  cout << "Symbols: ";
  printVectors(symbols);
}

void AFN::printVectors(vector<int> &vector) {
  cout << "{";

  for (int i=0; i<vector.size() - 1; i++) {
    cout << vector[i] << ", ";
  }

  cout << vector.back() <<  "}" << endl;
}
