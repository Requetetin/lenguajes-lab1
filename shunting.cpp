#include <iostream>
#include <stdio.h>
// CPP program to evaluate a given
// expression where tokens are
// separated by space.
#include <bits/stdc++.h>
#include <stack>
using namespace std;

int precedence(char op) {
  if(op == '*' || op == '+' || op == '?') 
  return 4;
  if(op == '.')
  return 3;
  if(op == '^' || op == '$')
  return 2;
  if(op == '|')
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
    if (regex[i] == '(') {
      ops.push(regex[i]);
    }
    else if (isalpha(regex[i])) {
      output.push(regex[i]);
      if (isalpha(regex[i+1])) {
        regex[i] = '.';
        i--;
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
        regex[i] = '.';
        i--;
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
          regex[i] = '.';
          i--;
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