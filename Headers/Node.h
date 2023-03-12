#include <iostream>
#include <string>
#include <set>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
  public:
    Node* left;
    Node* right;
    // Basic
    Node();

    // Leaf nodes
    Node(char, bool, int);

    // Unary operators
    Node(char, Node*);

    // Double operators
    Node(char, Node*, Node*);

    void setRoot() {isRoot=true;};

    Node* makeTree(string);

    void print(Node*);

    char getValue() {return value;};

    void computeFunctions(Node*);

    set<Node*> getNodeLeaves(Node*);

    int getLeafPosition() {return leafPosition;};

    bool getNullable() {return nullable;};
    set<int> getFirstPos() {return firstPos;};
    set<int> getLastPos() {return lastPos;};
    set<int> getNextPos() {return nextPos;};

    set<char> getSymbols() {return symbols;};

    void setSymbols(Node*);

  private:
    char value;
    bool isRoot = false;
    bool isLeaf = false;
    int leafPosition = -1;

    bool nullable;
    set<int> firstPos;
    set<int> lastPos;
    set<int> nextPos;

    void printSet(set<int>);

    bool calcNullable(Node*);
    set<int> calcFirstPos(Node*);
    set<int> calcLastPos(Node*);
    void calcNextPos(Node*);

    set<char> symbols;

};

#endif
