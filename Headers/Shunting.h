#include <stack>
#include <string>
#include <iostream>

using namespace std;

#ifndef SHUNTING_H
#define SHUNTING_H

class Shunting {
  public:
    Shunting();

    string toPostfix (string regex);

  private:
    int precedence(char);
};

#endif
