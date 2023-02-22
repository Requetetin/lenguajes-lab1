#include <stack>
#include <string>
#include <iostream>

using namespace std;

class Shunting {
  public:
    Shunting();

    stack<char> toPostfix (const string &initialExpression);

  private:
    int precedence(char);
};
