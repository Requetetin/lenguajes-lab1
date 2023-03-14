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
  for (int end: accepted) {
    cout << " " << end << " ";
  }
	cout << ";" << endl <<"node [shape = circle];" << endl;
  cout << initial << " [color=green];\n";
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

Transition AFD::getTransition(int initial, char sym) {
  for (Transition trans: transitions) {
    if (trans.getSource() == initial && trans.getSymbol() == sym) {
      return trans;
    }
  }
  return Transition(-1, -1, 'e');
}

bool AFD::isDistinguishable(vector<set<int>> PNew, int a, int b) {
  bool distinguishable = false;
  for (char sym: symbols) {
    Transition transA = getTransition(a, sym);
    Transition transB = getTransition(b, sym);
    if (transA.getDestiny() != transB.getDestiny()) {
      int subA, subB;
      for (int i=0; i<PNew.size(); i++) {
        if (PNew.at(i).count(transA.getDestiny())) {
          subA = i;
        }
        if (PNew.at(i).count(transB.getDestiny())) {
          subB = i;
        }
      }
      if (subA != subB) {
        distinguishable = true;
      }
    }
  }
  return distinguishable;
}

int AFD::indexOfSetWith(vector<set<int>> vc, int a) {
  for(int i=0; i<vc.size(); i++) {
    if (vc.at(i).count(a)) {
      return i;
    }
  }
  return -1;
}

AFD AFD::removeDeadStates() {
  // For every non acceptance state
  vector<int> deadStates;
  for (int state: states) {
    if (!count(accepted.begin(), accepted.end(), state)) {
      set<int> destinies;
      for (char sym: symbols) {
        destinies.insert(getTransition(state, sym).getDestiny());
      }
      if (destinies.size() == 1 && *destinies.begin() == state) {
        deadStates.push_back(state);
      }
    }
  }

  vector<Transition> newTransitions;
  if (deadStates.size() != 0) {
    for (int deadState: deadStates) {
      remove(states.begin(), states.end(), deadState);
      for (Transition trans: transitions) {
        if (trans.getSource() != deadState && trans.getDestiny() != deadState) {
          newTransitions.push_back(trans);
        }
      }
    }
    return AFD(initial, states, accepted, newTransitions);
  }
  return AFD(initial, states, accepted, transitions);
}

AFD AFD::minimize() {
  // Step 1: P0 = {{accepting states}, {remaining states}}
  vector<set<int>> POld;
  set<int> allStates;
  allStates.insert(states.begin(), states.end());
  set<int> finalStates;
  finalStates.insert(accepted.begin(), accepted.end());
  POld.push_back(finalStates);
  set<int> remainingStates;
  set_difference(allStates.begin(), allStates.end(), finalStates.begin(), finalStates.end(), inserter(remainingStates, end(remainingStates)));
  POld.push_back(remainingStates);

  vector<set<int>> PNew = POld;
  // cout << "Initial Partition: "<<endl;
  // for (set<int> localSet: PNew) {
  //   cout << "NEW SET: \n";
  //   for (int localState: localSet) {
  //     cout << localState << endl;
  //   }
  // }
  bool ending = false;
  vector<set<int>> partitioned;
  while (!ending) {
    // Step 2: Calculate P1
    
    partitioned.clear();
    for (set<int> subSet: PNew) {
      vector<int> vc(subSet.begin(), subSet.end());
      if (vc.size() > 1) {
        for(int i=0; i<vc.size(); i++) {
          for(int j=i+1; j<vc.size(); j++) {
            if (isDistinguishable(PNew, vc.at(i), vc.at(j))) {
              // cout << "DISTING" << vc.at(i) << ',' << vc.at(j) << endl;
              if (indexOfSetWith(partitioned, vc.at(i)) == -1 && indexOfSetWith(partitioned, vc.at(j)) == -1) {
                partitioned.push_back(set<int> {vc.at(i)});
                partitioned.push_back(set<int> {vc.at(j)});
              } else if (indexOfSetWith(partitioned, vc.at(i)) == -1) {
                partitioned.push_back(set<int> {vc.at(i)});
              } else if (indexOfSetWith(partitioned, vc.at(j)) == -1) {
                partitioned.push_back(set<int> {vc.at(j)});
              }
            } else {
              // cout << "NONDISTING" << vc.at(i) << ',' << vc.at(j) << endl;
              if (indexOfSetWith(partitioned, vc.at(i)) == -1 && indexOfSetWith(partitioned, vc.at(j)) == -1) {
                partitioned.push_back(set<int> {vc.at(i), vc.at(j)});
              } else if (indexOfSetWith(partitioned, vc.at(i)) == -1 && indexOfSetWith(partitioned, vc.at(j)) != -1) {
                partitioned.at(indexOfSetWith(partitioned, vc.at(j))).insert(vc.at(i));
              } else if (indexOfSetWith(partitioned, vc.at(j)) == -1 && indexOfSetWith(partitioned, vc.at(i)) != -1) {
                partitioned.at(indexOfSetWith(partitioned, vc.at(i))).insert(vc.at(j));
              } else if (indexOfSetWith(partitioned, vc.at(j)) != -1 && indexOfSetWith(partitioned, vc.at(i)) != -1) {
                if (indexOfSetWith(partitioned, vc.at(j)) != indexOfSetWith(partitioned, vc.at(i))) {
                  partitioned.erase(partitioned.begin() + indexOfSetWith(partitioned, vc.at(j)));
                  partitioned.at(indexOfSetWith(partitioned, vc.at(i))).insert(vc.at(j));
                }
              }
            }
          }
        }
      } else {
        partitioned.push_back(subSet);
        continue;
      }
    }
    // cout << "Next Partition: "<<endl;
    // for (set<int> localSet: partitioned) {
    //   cout << "NEW SET: \n";
    //   for (int localState: localSet) {
    //     cout << localState << endl;
    //   }
    // }

    if (PNew == partitioned) {
      ending = true;
    } else {
      PNew = partitioned;
    }
  }

  // cout << "Final Partition: "<<endl;
  // for (set<int> localSet: PNew) {
  //   cout << "NEW SET: \n";
  //   for (int localState: localSet) {
  //     cout << localState << endl;
  //   }
  // }

  vector<int> aStates;
  for (int i=0; i<PNew.size(); i++) {
    aStates.push_back(i);
  }

  vector<int> acceptanceStates;
  for (int i=0; i<PNew.size(); i++) {
    set<int> intersect;
    set_intersection(PNew.at(i).begin(), PNew.at(i).end(), finalStates.begin(), finalStates.end(), inserter(intersect, intersect.begin()));
    if (!intersect.empty())
      acceptanceStates.push_back(i);
  }

  vector<Transition> newTransitions;
  for (int i=0; i<PNew.size(); i++) {
    vector<int> localVc(PNew.at(i).begin(), PNew.at(i).end());
    for (char sym: symbols) {
      if (getTransition(localVc.at(0), sym).getDestiny() != -1) {
        int destiny = indexOfSetWith(PNew, getTransition(localVc.at(0), sym).getDestiny());
        newTransitions.push_back(Transition(i, destiny, sym));
      }
    }
  }

  int initialState;
  for (int i=0; i<PNew.size(); i++) {
    set<int> stateSet = PNew.at(i);
    if (stateSet.find(0) != stateSet.end()) {
      initialState = i;
    }
  }


  return AFD(initialState, aStates, acceptanceStates, newTransitions);
}
