#include "Node.h"
Node::Node(std::string str) {
    data = str;
    left = nullptr;
    right = nullptr;
    sub = 0;
}

Node::Node(std::string str, Node* L, Node* R, size_t s) {
    data = str;
    left = L;
    right = R;
    sub = s;
}


size_t Node::size(const Node* n) {
  if (!n)
    return 0;
   return 1 + Node::size(n->left) + Node::size(n->right);
}

static Node* copy(Node* other) {
    if(!other) {
        return nullptr;
    }
    Node* node = new Node(other->data);
    node->sub = other->sub;
    node->left = copy(other->left);
    node->right = copy(other->right);
    return node;
}
size_t Node::clean(Node* n) {
    if (!n) {
        return 0;
    }
    size_t cnt = clean(n->left) + clean(n->right) + 1;
    delete n;
    return cnt;
}
size_t Node::leftsize(const Node* n) {
    if (!n)
        return 0;
    return 1 + Node::size(n->left);
}

