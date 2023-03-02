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

void AFN::printVectors(vector<int> &vector) {
  cout << "{";

  for (int i=0; i<vector.size() - 1; i++) {
    cout << "\"" << vector[i] << "\", ";
  }

  cout << "\"" << vector.back() <<  "\"}," << endl;
}

void AFN::printVectors(vector<char> &vector) {
  cout << "{";

  for (int i=0; i<vector.size() - 1; i++) {
    cout << "\"" << vector[i] << "\", ";
  }

  cout << "\"" << vector.back() <<  "\"}," << endl;
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

AFN AFN::orAutomata(AFN &aut1, AFN &aut2) {
  int startState = AFN::nextState();

  Transition firstTrans(startState, aut1.initial, 'e');
  Transition secondTrans(startState, aut2.initial, 'e');

  vector<Transition> allTransitions = {firstTrans, secondTrans};

  int endState = AFN::nextState();
  for (int state: aut1.accepted) {
    allTransitions.push_back(Transition(state, endState, 'e'));
  }
  for (int state: aut2.accepted) {
    allTransitions.push_back(Transition(state, endState, 'e'));
  }

  for (Transition transition: aut1.transitions) {
    allTransitions.push_back(transition);
  }
  for (Transition transition: aut2.transitions) {
    allTransitions.push_back(transition);
  }

  vector<int> acceptedStates = {endState};

  vector<int> allStates = {startState, endState};

  for (int state: aut1.states) {
    allStates.push_back(state);
  }

  for (int state: aut2.states) {
    allStates.push_back(state);
  }

  return AFN(startState, allStates, acceptedStates, allTransitions);

}

AFN AFN::conccatenationAutomata(AFN &aut1, AFN &aut2) {
  int startState = aut1.initial;
  vector<int> acceptedStates = aut2.accepted;

  vector<int> allStates;
  for (int state: aut1.states) {
    allStates.push_back(state);
  }
  for (int state: aut2.states) {
    allStates.push_back(state);
  }

  vector<Transition> allTransitions;
  for (Transition transition: aut1.transitions) {
    allTransitions.push_back(transition);
  }
  for (Transition transition: aut2.transitions) {
    allTransitions.push_back(transition);
  }

  for (int accept: aut1.accepted) {
    allTransitions.push_back(Transition(accept, aut2.initial, 'e'));
  }

  return AFN(startState, allStates, acceptedStates, allTransitions);
}

AFN AFN::kleeneAutomata(AFN &aut1) {
  int startState = AFN::nextState();
  int endState = AFN::nextState();

  vector<int> acceptedStates = {endState};

  vector<int> allStates = {startState, endState};
  for (int state: aut1.states) {
    allStates.push_back(state);
  }

  vector<Transition> allTransitions;
  for (Transition transition: aut1.transitions) {
    allTransitions.push_back(transition);
  }

  allTransitions.push_back(Transition(startState, endState, 'e'));
  allTransitions.push_back(Transition(startState, aut1.initial, 'e'));
  for (int accept: aut1.accepted) {
    allTransitions.push_back(Transition(accept, aut1.initial, 'e'));
    allTransitions.push_back(Transition(accept, endState, 'e'));
  }

  return AFN(startState, allStates, acceptedStates, allTransitions);
}

void AFN::printDotNotation() {
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

set<int> AFN::eClosure() {
  set<int> a;
  return a;
}

set<int> AFN::eClosure(set<int> initials) {
  set<int> a;
  return a;
}

set<int> AFN::move(set<int> states, char symbol) {
  set<int> a;
  return a;
} 
