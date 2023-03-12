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
  cout << "\nString being converted to a tree: " << regex << endl;
  stack<Node*> nodeStack;
  int leafNumber = 1;
  for (char exp: regex) {
    if (isalnum(exp) || exp == '#') {
      Node* node = new Node(exp, true, leafNumber);
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

void Node::printSet(set<int> set) {
  cout << '{';
  for (int value : set) {
    cout << value << ", ";
  }
  cout << '}';
}

bool Node::calcNullable(Node* node) {
  if (node->value == 'e') {
    return true;
  } else if (node->isLeaf) {
    return false;
  } else if (node->value == '|') {
    if (node->left->nullable || node->right->nullable)
      return true;
    return false;
  } else if (node->value == '.') {
    if (node->left->nullable && node->right->nullable)
      return true;
    return false;
  } else if (node->value == '*') {
    return true;
  }
  return false;
}

set<int> Node::calcFirstPos(Node* node) {
  set<int> a;
  vector<int> temp;
  if (node->value == 'e') {
    return a;
  } else if (node->isLeaf) {
    a.insert(node->leafPosition);
    return a;
  } else if (node->value == '|') {
    set<int> left = node->left->firstPos;
    set<int> right = node->right->firstPos;
    set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(temp));
    copy(temp.begin(), temp.end(), inserter(a, a.end()));
    return a;
  } else if (node->value == '.') {
    if (node->left->nullable) {
      set<int> left = node->left->firstPos;
      set<int> right = node->right->firstPos;
      set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(temp));
      copy(temp.begin(), temp.end(), inserter(a, a.end()));
      return a;
    } else {
      a = node->left->firstPos;
      return a;
    }
  } else if (node->value == '*') {
    a = node->left->firstPos;
    return a;
  }
  return a;
}

set<int> Node::calcLastPos(Node* node) {
  set<int> a;
  vector<int> temp;
  if (node->value == 'e') {
    return a;
  } else if (node->isLeaf) {
    a.insert(node->leafPosition);
    return a;
  } else if (node->value == '|') {
    set<int> left = node->left->lastPos;
    set<int> right = node->right->lastPos;
    set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(temp));
    copy(temp.begin(), temp.end(), inserter(a, a.end()));
    return a;
  } else if (node->value == '.') {
    if (node->right->nullable) {
      set<int> left = node->left->lastPos;
      set<int> right = node->right->lastPos;
      set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(temp));
      copy(temp.begin(), temp.end(), inserter(a, a.end()));
      return a;
    } else {
      a = node->right->lastPos;
      return a;
    }
  } else if (node->value == '*') {
    a = node->left->lastPos;
    return a;
  }
  return a;
}

void Node::calcNextPos(Node* node) {
  if (node->value == '*') {
    set<Node*> leaves = node->getNodeLeaves(node);
    for (int nodeId : node->lastPos) {
      for (Node* leaf: leaves) {
        if (leaf->leafPosition == nodeId) {
          leaf->nextPos.insert(node->firstPos.begin(), node->firstPos.end());
        }
      }
    }
  } else if (node->value == '.') {
    set<Node*> leaves = node->getNodeLeaves(node);
    for (int nodeId: node->left->lastPos) {
      for (Node* leaf: leaves) {
        if (leaf->leafPosition == nodeId) {
          leaf->nextPos.insert(node->right->firstPos.begin(), node->right->firstPos.end());
        }
      }
    }
  }
}

void Node::print(Node* node) {
  if (node == NULL) {
    return;
  }

  print(node->left);
  print(node->right);
  cout << 
    node->value << "\n" <<
    "Leaf: " << node->isLeaf << "\n"; 
  if (node->isLeaf) {
    cout << "Leaf Id: " << node->leafPosition << "\n";
  }
  cout <<
    "Root: " << node->isRoot << "\n" <<
    "Nullable: " << node->nullable << "\n" <<
    "First Pos: ";
    printSet(node->firstPos);
    cout << "\nLast Pos: ";
    printSet(node->lastPos);
    if (node->isLeaf) {
      cout << "\nFollow Pos: ";
      printSet(node->nextPos);
    }
  cout << endl;
}

void Node::computeFunctions(Node* node) {
  if (node == NULL)
    return;

  computeFunctions(node->left);
  computeFunctions(node->right);

  node->nullable = node->calcNullable(node);
  node->firstPos = node->calcFirstPos(node);
  node->lastPos = node->calcLastPos(node);
  node->calcNextPos(node);
}

set<Node*> Node::getNodeLeaves(Node* node) {
  set<Node*> nodeSet;
  // Add leaves
  if (node->left != NULL && node->left->isLeaf) {
    nodeSet.insert(node->left);
  }
  if (node->right != NULL && node->right->isLeaf) {
    nodeSet.insert(node->right);
  }

  // If not leaves, go through them
  if (node->left != NULL && !node->left->isLeaf) {
    set<Node*> temp = getNodeLeaves(node->left);
    nodeSet.insert(temp.begin(), temp.end());
  }
  if (node->right != NULL && !node->right->isLeaf) {
    set<Node*> temp = getNodeLeaves(node->right);
    nodeSet.insert(temp.begin(), temp.end());
  }
  return nodeSet;

}

void Node::setSymbols(Node* node) {
  set<Node*> leaves = getNodeLeaves(node);

  for (Node* leaf : leaves) {
    if (leaf->value != '#' && leaf->value != 'e')
      symbols.insert(leaf->value);
  }
}
