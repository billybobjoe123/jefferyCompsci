#include <string>
#include <cstddef>
#ifndef NODE_H
#define NODE_H

// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.
class Node
{
    public:
    std::string data;
    Node* left;
    Node* right;

    size_t sub;
    Node(std::string str);
    Node(std::string str, Node* L, Node* R, size_t s);
    size_t size(const Node* n);
    size_t clean(Node* n);
    size_t countless(Node* n, std::string data) const;   

};



#endif
