#include <iostream>

#include <set>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
  public:
    // Basic
    Node();

    // Leaf nodes
    Node(char, bool, int);

    // Unary operators
    Node(char, Node*);

    // Double operators
    Node(char, Node*, Node*);

    void setRoot() {isRoot=true;};

  private:
    char value;
    bool isRoot = false;
    bool isLeaf = false;
    int leafPosition = NULL;
    static Node* left;
    static Node* right;

    bool nullable;
    set<int> firstPos;
    set<int> lastPos;
    set<int> nextPos;


    bool nullable();
    set<int> firstPos();
    set<int> lastPos();
    set<int> nextPos();

};

#endif
