#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include "Transition.h"
#include "AFD.h"

using namespace std;

#ifndef AFN_H
#define AFN_H

class AFN {
  public:
    AFN();
    AFN(int initialState, vector<int> allStates, vector<int> acceptedStates, vector<Transition> allTransitions);

    void print();

    void printDotNotation();

    bool simulate();

    static int nextState() {return maxState++;};
    int getInitial() {return initial;};

    static AFN symbolAutomata(char sym);
    static AFN conccatenationAutomata(AFN &aut1, AFN &aut2);
    static AFN orAutomata(AFN &aut1, AFN &aut2);
    static AFN kleeneAutomata(AFN &aut1);

    set<int> eClosure(int, set<int>);
    set<int> eClosure(set<int>);
    set<int> move(set<int>, char);

    AFD toAFD();

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