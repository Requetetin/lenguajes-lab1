#include "Headers/AFD.h"

AFD::AFD() = default;

int AFD::maxState = 0;

AFD::AFD(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions) {
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

void AFD::print() {
  cout << "initial_state=\"" << initial << "\"," << endl;
  cout << "states=";
  printVectors(states);
  cout << "final_states=";
  printVectors(accepted);
  cout << "transitions={" << endl;
  for (Transition &transition: transitions) {
    transition.print();
  }
  cout << "}," << endl;
  cout << "input_symbols=";
  printVectors(symbols);
}

void AFD::printVectors(vector<int> &vector) {
  cout << "{";

  for (int i=0; i<vector.size() - 1; i++) {
    cout << "\"" << vector[i] << "\", ";
  }

  cout << "\"" << vector.back() <<  "\"}," << endl;
}

void AFD::printVectors(vector<char> &vector) {
  cout << "{";

  for (int i=0; i<vector.size() - 1; i++) {
    cout << "\"" << vector[i] << "\", ";
  }

  cout << "\"" << vector.back() <<  "\"}," << endl;
}

void AFD::printDotNotation() {
  cout << "digraph finite_state_machine {" << endl;
	cout << "fontname=\"Helvetica,Arial,sans-serif\"" << endl;
	cout << "node [fontname=\"Helvetica,Arial,sans-serif\"]" << endl;
	cout << "edge [fontname=\"Helvetica,Arial,sans-serif\"]" << endl;
	cout << "rankdir=LR;" << endl;
	cout << "node [shape = doublecircle]; ";
  cout << initial << " ";
  for (int end: accepted) {
    cout << " " << end << " ";
  }
	cout << ";" << endl <<"node [shape = circle];" << endl;
	for (Transition &transition: transitions) {
    transition.printDot();
  }
  cout << "}";
}

int AFD::move(int start, char moveSymbol) {
  int next = -1;
  for (Transition transition: transitions) {
    if (transition.getSymbol() == moveSymbol && transition.getSource() == start) {
      next = transition.getDestiny();
    }
  }
  return next;
} 

bool AFD::simulate() {
  set<int> F;
  for (int accState: accepted) {
    F.insert(accState);
  }
  string testString;
  cout << "\nType the testing string\n";
  cin >> testString;
  cout << "Starting test for: " << testString << "\n";
  int s = initial;
  for (int i = 0; i < testString.length(); i++) {
    s = move(s, testString[i]);
  }
  if (F.count(s) != 0)
    return true;
  return false;
}
