#include "Headers/Shunting.h"

Shunting::Shunting() = default;

int Shunting::precedence(char op) {
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

string Shunting::toPostfix (string regex) {
  string output;
  stack <char> ops;

  for(int i=0; regex[i] != '\0'; i++) {
    if (regex[i] == ' ') {
      printf("Your expression contains a whitespace at %d, please remove to continue", i);
      exit(-1);
      continue;
    }
    if (regex[i] == '(') {
      ops.push(regex[i]);
    }
    else if (isalnum(regex[i])) {
      output +=regex[i];
      if (isalnum(regex[i+1]) || regex[i+1] == '(') {
        regex[i] = '.';
        i--;
      }
    }
    else if (regex[i] == ')') {
      while(!ops.empty() && ops.top() != '(') {
        char op = ops.top();
        ops.pop();
        output += op;
      }
      if (!ops.empty()) {
        ops.pop();
      }
      if (isalnum(regex[i+1]) || regex[i+1] == '(') {
        regex[i] = '.';
        i--;
      }
    }
    else {
      while(!ops.empty() && precedence(ops.top()) >= precedence(regex[i])) {
        char op = ops.top();
        ops.pop();
        output += op;
      }
      ops.push(regex[i]);
      if (regex[i] == '*' || regex[i] == '+' || regex[i] == '?') {
        if (isalnum(regex[i+1]) || regex[i+1] == '(') {
          regex[i] = '.';
          i--;
        }
      }
    }
  }

  while(!ops.empty()) {
    char op = ops.top();
    ops.pop();
    output += op;
  }

  return output;
}