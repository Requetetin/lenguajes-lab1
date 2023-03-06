#include <vector>
#include <set>
#include <algorithm>
#include "Transition.h"

using namespace std;

#ifndef AFD_H
#define AFD_H

class AFD {
  public:
    AFD();
    AFD(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions);

    void print();

    void printDotNotation();

    bool simulate();

    static int nextState() {return maxState++;};
    int getInitial() {return initial;};

    set<int> eClosure(int);
    set<int> eClosure(set<int>);
    set<int> move(set<int>, char);

  private:
    int initial;
    vector<int> states;
    vector<int> accepted;
    vector<char> symbols;
    vector<Transition> transitions;
    static int maxState;
    void printVectors(vector<int> &vector);
    void printVectors(vector<char> &vector);
};

#endif