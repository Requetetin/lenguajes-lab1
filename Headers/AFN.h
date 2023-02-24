#include <vector>
#include <algorithm>
#include "Transition.h"

using namespace std;

#ifndef AFN_H
#define AFN_H

class AFN {
  public:
    AFN();
    AFN(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions);

    void print();

  private:
    int initial;
    vector<int> states;
    vector<int> accepted;
    vector<int> symbols;
    vector<Transition> transitions;
    void printVectors(vector<int> &vector);
};

#endif