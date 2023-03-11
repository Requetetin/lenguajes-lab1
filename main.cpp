#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stack>

#include "Headers/AFD.h"
#include "Headers/AFN.h"
#include "Headers/Cleaner.h"
#include "Headers/Node.h"
#include "Headers/Reviewer.h"
#include "Headers/Shunting.h"
#include "Headers/Transition.h"

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

  // if (finalAutomata.simulate()) {
  //   cout << "\nTHE STRING IS VALID";
  // } else {
  //   cout << "\nTHE STRING IS INVALID";
  // }

  AFD translated = finalAutomata.toAFD();
  translated.printDotNotation();
  // if (translated.simulate()) {
  //   cout << "\nTHE STRING IS VALID";
  // } else {
  //   cout << "\nTHE STRING IS INVALID";
  // }

  Node* root;
  root = root->makeTree(output);
  root->print(root);
  return 0;
}