#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stack>

#include "Headers/Transition.h"
#include "Headers/Shunting.h"
#include "Headers/AFN.h"
#include "Headers/Cleaner.h"
#include "Headers/Reviewer.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("No argument was provided");
    exit(-1);
  }
  cout << "Regex input: " << argv[1] << endl;
  Cleaner cleaner;
  string cleanRegex = cleaner.cleanString(argv[1]);
  cout << "CLEANED: " + cleanRegex << endl;
  Reviewer review(cleanRegex);
  Shunting shunting;
  string output = shunting.toPostfix(cleanRegex);
  cout << "POSTFIX: " + output << endl;

  stack<AFN> afnStack;

  for (char exp : output) {
    if (exp == '*') {
      AFN automata = afnStack.top();
      afnStack.pop();

      afnStack.push(AFN::kleeneAutomata(automata));
    } else if (exp == '|') {
      AFN secondAutomata = afnStack.top();
      afnStack.pop();

      AFN firstAutomata = afnStack.top();
      afnStack.pop();

      afnStack.push(AFN::orAutomata(firstAutomata, secondAutomata));
    } else if (exp == '.') {
      AFN secondAutomata = afnStack.top();
      afnStack.pop();

      AFN firstAutomata = afnStack.top();
      afnStack.pop();

      afnStack.push(AFN::conccatenationAutomata(firstAutomata, secondAutomata));
    } else {
      afnStack.push(AFN::symbolAutomata(exp));
    }
  }

  AFN finalAutomata = afnStack.top();
  afnStack.pop();
  finalAutomata.print();
  cout << "\n\nDOT NOTATION:\n";
  finalAutomata.printDotNotation();

  set<int> eClosureInitial = finalAutomata.eClosure(finalAutomata.getInitial());
  cout << "\nECLOSURE INITIAL:\n";
  for (auto& str : eClosureInitial) {
      cout << str << ' ';
  }

  set<int> moveA = finalAutomata.move(eClosureInitial, 'a');
  cout << "\nMOVE ECLOSURE INITIAL:\n";
  for (auto& str : moveA) {
      cout << str << ' ';
  }

  return 0;
}