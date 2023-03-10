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

    int move(int, char);

    AFD minimize();

    AFD removeDeadStates();

  private:
    int initial;
    vector<int> states;
    vector<int> accepted;
    vector<char> symbols;
    vector<Transition> transitions;
    static int maxState;
    void printVectors(vector<int> &vector);
    void printVectors(vector<char> &vector);

    bool isDistinguishable(vector<set<int>>, int, int);
    Transition getTransition(int, char);
    int indexOfSetWith(vector<set<int>>, int);
};

#endif