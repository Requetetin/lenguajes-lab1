#include <iostream>

using namespace std;

class Transition {
  public:
    Transition();
    
    Transition(int, int, char);

    void print();

    int getSource() { return source; }

    int getDestiny() { return destiny; }

    char getSymbol() { return symbol; }

    int getSymbolEquiv() { return symbolEquivalent; }

  private:
    int source;
    int destiny;
    char symbol;
    int symbolEquivalent;
};
