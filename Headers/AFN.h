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

    static int nextState() {return maxState++;};

    static AFN symbolAutomata(char sym);
    static AFN conccatenationAutomata(AFN &aut1, AFN &aut2);
    static AFN orAutomata(AFN &aut1, AFN &aut2);
    static AFN kleeneAutomata(AFN &aut1);

  private:
    int initial;
    vector<int> states;
    vector<int> accepted;
    vector<int> symbols;
    vector<Transition> transitions;
    static int maxState;
    void printVectors(vector<int> &vector);
};

#endif