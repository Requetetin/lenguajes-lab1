#include <iostream>
#include <stdio.h>
#include <set>
// CPP program to evaluate a given
// expression where tokens are
// separated by space.
#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
  if(op == '*' || op == '+' || op == '?') 
  return 3;
  if(op == '.')
  return 2;
  if(op == '^' || op == '$')
  return 1;
  return 0;
}
int main () {
  char regex[50];
  printf("Introducir expresion regular: ");
  scanf("%s", regex);
  stack <char> output;
  stack <char> ops;

  for(int i=0; regex[i] != '\0'; i++) {
    if (!ops.empty()) {
      
      cout << ops.top() << "\n\n";
    }
    if (regex[i] == '(') {
      ops.push(regex[i]);
    }
    else if (isalpha(regex[i])) {
      output.push(regex[i]);
      if (isalpha(regex[i+1])) {
        ops.push('.');
      }
    }
    else if (regex[i] == ')') {
      while(!ops.empty() && ops.top() != '(') {
        char op = ops.top();
        ops.pop();
        output.push(op);
      }
      if (!ops.empty()) {
        ops.pop();
      }
      if (isalpha(regex[i+1])) {
        ops.push('.');
      }
    }
    else {
      while(!ops.empty() && precedence(ops.top()) >= precedence(regex[i])) {
        char op = ops.top();
        ops.pop();
        output.push(op);
      }
      ops.push(regex[i]);
      if (regex[i] == '*' || regex[i] == '+' || regex[i] == '?') {
        if (isalpha(regex[i+1])) {
          ops.push('.');
        }
      }
    }
  }

  while(!ops.empty()) {
    char op = ops.top();
    ops.pop();
    output.push(op);
  }

  while(!output.empty()) {
    char topChar = output.top();
    cout << topChar << '\n';
    output.pop();
  }

  return 0;
}