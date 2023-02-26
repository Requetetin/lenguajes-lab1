#include <algorithm>
#include <string>

using namespace std;

#ifndef REVIEWER_H
#define REVIEWER_H

class Reviewer {
  public:
    Reviewer(string regex);

  private:
    void balancedParentheses(string regex);
    void validOperations(string regex);
};

#endif
