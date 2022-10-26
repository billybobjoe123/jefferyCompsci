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


size_t Node::clean(Node* n) {
    if (!n) {
        return 0;
    }
    size_t cnt = clean(n->left) + clean(n->right) + 1;
    delete n;
    return cnt;
}
size_t Node::countless(Node* root, std::string data) const {
    Node* tmp = root;
    size_t cnt = 0;
    if (tmp) {
        if (data > tmp->data) {
            cnt += countless(tmp->left, data);

            cnt += countless(tmp->right, data);
        } else {
            cnt += 1 + countless(tmp->left, data);
        }
    }
    return cnt;
}




