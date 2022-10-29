#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.
class numberNode: public AST {
    private:
    double data;
    public:
    numberNode(int val);
    std::string prefix()  const;
    std::string postfix() const;
    double value()   const;
};
class operatorNode: public AST {
    private:
    std::string data; //can only be + - /
    public:
    AST* left;
    AST* right;

    operatorNode(std::string val);
    ~operatorNode();
    std::string prefix()  const;
    std::string postfix() const;
    double value()   const;
};


#endif
