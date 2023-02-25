#include "Headers/AFN.h"

AFN::AFN() = default;

int AFN::maxState = 0;

AFN::AFN(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions) {
  this->initial = initialState;
  this->states = allStates;
  this->accepted = acceptedStates;
  this->transitions = allTransitions;
  for (Transition &transition : transitions) {
    int transitionSymbol = transition.getSymbolEquiv();
    if (!count(symbols.begin(), symbols.end(), transitionSymbol)) {
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

AFN AFN::symbolAutomata(char sym) {
  int startState = AFN::nextState();
  int endState = AFN::nextState();

  vector<int> allStates = {startState, endState};

  vector<int> acceptedStates = {endState};

  Transition symbolTrans(startState, endState, sym);
  vector<Transition> allTransitions = {symbolTrans};

  return AFN(startState, allStates, acceptedStates, allTransitions);
}
