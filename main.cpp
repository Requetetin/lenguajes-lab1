#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stack>

#include "Headers/Transition.h"
#include "Headers/Shunting.h"
#include "Headers/AFN.h"
#include "Headers/Cleaner.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("No argument was provided");
    exit(-1);
  }
  cout << "Regex input: " << argv[1] << endl;
  Cleaner cleaner;
  string cleanRegex = cleaner.cleanString(argv[1]);
  cout << cleanRegex << endl;
  Shunting shunting;
  string output = shunting.toPostfix(cleanRegex);
  cout << output << endl;
  AFN father;
  AFN trial = father.symbolAutomata('a');
  trial.print();

  return 0;
}