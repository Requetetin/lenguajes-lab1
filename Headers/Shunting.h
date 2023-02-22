#include <stack>
#include <string>
#include <iostream>

using namespace std;

class Shunting {
  public:
    Shunting();

    string toPostfix (string regex);

  private:
    int precedence(char);
};
