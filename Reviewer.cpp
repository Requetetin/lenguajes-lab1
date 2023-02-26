#include "Headers/Reviewer.h"
#include <iostream>

Reviewer::Reviewer(string regex) {
  balancedParentheses(regex);
  validOperations(regex);
}

void Reviewer::balancedParentheses(string regex) {
  if (count(regex.begin(), regex.end(), '(') != count(regex.begin(), regex.end(), ')')) {
    cout << "ERROR! Parentheses not balanced, enter a valid input" << endl;
    exit(-1);
  }
}

void Reviewer::validOperations(string regex) {
  for (int i=0; i<regex.size(); i++) {
    if (regex[i] == '|') {
      if (!isalnum(regex[i-1]) || !isalnum(regex[i + 1])) {
        cout << "ERROR! Invalid | operation at index: " << i << endl;
        exit(-1);
      }
    } else if (regex[i] == '*') {
      if (!isalnum(regex[i-1]) && regex[i-1] != ')') {
        cout << "ERROR! Invalid * operation at index: " << i << endl;
        exit(-1);
      }
    }
  }

  if (regex[0] == '*') {
    cout << "ERROR! Can't use operator * at the start" << endl;
    exit(-1);
  }
}
