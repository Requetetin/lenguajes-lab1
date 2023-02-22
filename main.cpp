#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stack>

#include "Headers/Transition.h"
#include "Headers/Shunting.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("No argument was provided");
    exit(-1);
  }
  cout << "Regex input: " << argv[1] << endl;
  Shunting shunting;
  string output = shunting.toPostfix(argv[1]);
  cout << output << endl;
  Transition trial(1, 2, 'a'); 
  trial.print();

  return 0;
}