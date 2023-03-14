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

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();

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

  cout << "\n\nAutomata no determinista: " << endl;
  AFN finalAutomata = afnStack.top();
  afnStack.pop();
  cout << "\n\nDOT NOTATION:\n";
  finalAutomata.printDotNotation();

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();

  cout << "\n\nSimulando Automata no determinista: " << endl;
  if (finalAutomata.simulate()) {
    cout << "\nTHE STRING IS VALID";
  } else {
    cout << "\nTHE STRING IS INVALID";
  }

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();
  cin.get();

  cout << "\n\nAutomata no determinista a determinista: " << endl;
  AFD translated = finalAutomata.toAFD();
  translated.printDotNotation();

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();

  cout << "\n\nSimulando Automata no determinista a determinista: " << endl;
  if (translated.simulate()) {
    cout << "\nTHE STRING IS VALID";
  } else {
    cout << "\nTHE STRING IS INVALID";
  }

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();
  cin.get();

  cout << "\n\nAutomata determinista directo: " << endl;
  string directOutput = output;
  directOutput.push_back('#');
  directOutput.push_back('.');
  Node* root;
  root = root->makeTree(directOutput);
  root->setRoot();
  root->computeFunctions(root);
  root->setSymbols(root);
  set<char> symbols = root->getSymbols();

  set<Node*> treeLeaves = root->getNodeLeaves(root);
  int finalIndex;
  for (Node* leaf: treeLeaves) {
    if (leaf->getValue() == '#') {
      finalIndex = leaf->getLeafPosition();
    }
  }
  vector<set<int>> Dstates;
  vector<bool> DstatesMarks;
  vector<Transition> Dtrans;
  Dstates.push_back(root->getFirstPos());
  DstatesMarks.push_back(false);

  bool ending = 0;
  while (!ending) {
    auto it = find(DstatesMarks.begin(), DstatesMarks.end(), false);
    if (it != DstatesMarks.end()) {
      int index = it - DstatesMarks.begin();
      DstatesMarks.at(index) = true;
      for (char sym: symbols) {
        set<int> corresponding;
        for (int leafId: Dstates.at(index)) {
          for (Node* leaf: treeLeaves) {
            if (leaf->getValue() == sym && find(Dstates.at(index).begin(), Dstates.at(index).end(), leaf->getLeafPosition()) != Dstates.at(index).end()) {
              corresponding.insert(leaf->getLeafPosition());
            }
          }
        }
        set<int> next;
        for (int id: corresponding) {
          for (Node* leaf: treeLeaves) {
            if (leaf->getLeafPosition() == id) {
              set<int> leafNextPos = leaf->getNextPos();
              next.insert(leafNextPos.begin(), leafNextPos.end());
            }
          }
        }

        if (find(Dstates.begin(), Dstates.end(), next) == Dstates.end()) {
          Dstates.push_back(next);
          DstatesMarks.push_back(false);
        }

        int destinyIndex = find(Dstates.begin(), Dstates.end(), next) - Dstates.begin();
        Dtrans.push_back(Transition(index, destinyIndex, sym));
      }
    } else {
      ending = 1;
    }
  }

  vector<int> allStates;
  for (int i=0; i<Dstates.size(); i++) {
    allStates.push_back(i);
  }
  vector<int> acceptedStates;
  for (int i=0; i<Dstates.size(); i++) {
    if (count(Dstates.at(i).begin(), Dstates.at(i).end(), finalIndex)) {
      acceptedStates.push_back(i);
    }
  }

  AFD direct(0, allStates, acceptedStates, Dtrans);
  direct.printDotNotation();

  cout << "\nPRESS ENTER TO CONTINUE...";
  cin.get();

  cout << "Simulando determinista directo: " << endl;
  if (direct.simulate()) {
    cout << "\nTHE STRING IS VALID";
  } else {
    cout << "\nTHE STRING IS INVALID";
  }

  cout << "\n\nAutomata determinista minimizado: " << endl;
  AFD minimized = direct.minimize();
  minimized.printDotNotation();
  cout << "\nEND\n";
  return 0;
}