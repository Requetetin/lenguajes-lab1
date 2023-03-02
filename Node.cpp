#include "Headers/Node.h"

Node::Node() = default;

Node::Node(char value, bool isLeaf, int leafPosition) {
  this->value = value;
  this->isLeaf = isLeaf;
  this->leafPosition = leafPosition;
}

Node::Node(char value, Node* left) {
  this->value = value;
  this->left = left;
}

Node::Node(char value, Node* left, Node* right) {
  this->value = value;
  this->left = left;
  this->right = right;
}

bool Node::nullable() {
  return true;
}

set<int> Node::firstPos() {
  set<int> a;
  return a;
}

set<int> Node::lastPos() {
  set<int> a;
  return a;
}

set<int> Node::nextPos() {
  set<int> a;
  return a;
}
