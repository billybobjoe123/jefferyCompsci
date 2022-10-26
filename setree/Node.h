#include <string>
#include <cstddef>
#include <iostream>
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
    static std::string findBiggest(Node* node) {
        if (node->right) {
            return findBiggest(node->right);
        } 
        else {
            return node->data;
        }
    }
    
    static void Remove(Node* node, Node* match, bool left ) {
        Node* temp;
        std::string val = node->data;
        std::string biggestInLeftTree;

        //zero children
        if (!node->left && !node->right) {
            temp = match;
            if(left) {
                node->left = nullptr;
            }
            else {
                node->right = nullptr;
            }
            delete temp;
            std::cout<<"node containing value "<<val<<" was deleted\n";
        }
        //one child
        else if(!match->left && match->right) {
            if (left) {
                node->left = match->right;
            }
            else {
                node->right = match->right;
            }
            match->right = nullptr;
            temp = match;
            delete temp;
            std::cout<<"node containing value "<<val<<" was deleted\n";
        }
        else if(match->left && !match->right) {
            if (left) {
                node->left = match->left;
            }
            else {
                node->right = match->left;
            }
            match->left = nullptr;
            temp = match;
            delete temp;
            std::cout<<"node containing value "<<val<<" was deleted\n";
        }
        //two children
        else {
            biggestInLeftTree = findBiggest(match->left);
            Node::deleteNode(match,biggestInLeftTree);
            match->data = biggestInLeftTree;
        }
    }
    static size_t deleteNode(Node* node, std::string Value) {
    if(node) {
        if(Value < node->data && node->left) {
            if (node->left->data==Value) {
                Node::Remove(node,node->left, true);
            } 
            else {
                deleteNode(node->left, Value);
            }
        }    
        else if(Value > node->data && node->right) {
            if (node->right->data==Value) {
                Node::Remove(node,node->right, false);
            } 
            else {
                deleteNode(node->right, Value);
            } 
        } 
        else {
            return 0;
        }   
         return 1;
    } 
    else {
        return 0;
    }
}   
};



#endif
