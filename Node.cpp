#include "Headers/Node.h"

Node::Node() = default;

Node::Node(char value, bool isLeaf, int leafPosition) {
  this->value = value;
  this->isLeaf = isLeaf;
  this->leafPosition = leafPosition;
  this->left = NULL;
  this->right = NULL;
}

Node::Node(char value, Node* left) {
  this->value = value;
  this->left = left;
  this->right = NULL;
}

Node::Node(char value, Node* left, Node* right) {
  this->value = value;
  this->left = left;
  this->right = right;
}

Node* Node::makeTree(string regex) {
  stack<Node*> nodeStack;
  int leafNumber = 1;
  for (char exp: regex) {
    if (isalnum(exp) || exp == '#') {
      Node* node = new Node(exp, true, 1);
      nodeStack.push(node);
      leafNumber++;
    } else {
      if (exp == '|' || exp == '.') {
        Node* right = nodeStack.top();
        nodeStack.pop();
        Node* left = nodeStack.top();
        nodeStack.pop();
        Node* newNode = new Node(exp, left, right);
        nodeStack.push(newNode);
      } else {
        Node* left = nodeStack.top();
        nodeStack.pop();
        Node* newNode = new Node(exp, left);
        nodeStack.push(newNode);
      }
    }
  }
  return nodeStack.top();
}

bool Node::calcNullable() {
  return true;
}

set<int> Node::calcFirstPos() {
  set<int> a;
  return a;
}

set<int> Node::calcLastPos() {
  set<int> a;
  return a;
}

set<int> Node::calcNextPos() {
  set<int> a;
  return a;
}

void Node::print(Node* node) {
  if (node == NULL) {
    return;
  }

  print(node->left);
  print(node->right);
  cout << node->value << endl;


}
