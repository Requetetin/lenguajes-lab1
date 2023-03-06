#include "Headers/Node.h"

Node::Node() = default;

Node::Node(char value, bool isLeaf, int leafPosition) {
  this->value = value;
  this->isLeaf = isLeaf;
  this->leafPosition = leafPosition;
}

// Node::Node(char value, Node left) {
//   this->value = value;
//   this->left = left;
// }

// Node::Node(char value, Node left, Node right) {
//   this->value = value;
//   this->left = left;
//   this->right = right;
// }

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
