#ifndef STACK_H
#define STACK_H
#include "AST.h"
#include "Nodes.h"
// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.
class Stack {
    private:
    AST* *array;
    size_t index;
    size_t size;
    void resize();
    public:
    Stack();
    ~Stack();
    void push(AST* node);
    size_t indexSize();
    AST* pop();


    

};

#endif
