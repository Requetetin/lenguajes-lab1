#include <string>
#include <algorithm>

using namespace std;

#ifndef CLEANER_H
#define CLEANER_H

class Cleaner {
  public:
    Cleaner();
    string cleanString(string regex);

  private:
    string removeSpaces(string regex);
    string replacePlus(string regex);
    string replaceQuestion(string regex);
};

#endif
