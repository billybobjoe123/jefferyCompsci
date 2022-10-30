#include "AST.h"
#include "Nodes.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Stack.h"

AST* AST::parse(const std::string& expression) {
    if (expression == "") {
        throw std::runtime_error("No input.");
    }
    Stack *stack = new Stack();
    std::istringstream mystream(expression);
    std::string str;
    
    while(mystream >> str) {
        double number;
        try {
            size_t *usedChar;
            size_t numb = 0;
            usedChar = &numb;
            number = std::stod(str, usedChar);
            if (*usedChar<str.size()) {
                
                throw std::runtime_error("Invalid token: " + str);
            }
            numberNode *n = new numberNode(number);
            stack->push(n); 
        }
        catch(std::runtime_error) {
            if (str=="~") {
                operatorNode* node = new operatorNode(str);
                node->left = stack->pop();
                if (!node->left) { 
                    delete node;
                    delete stack;
                    node = nullptr;
                    stack = nullptr;
                    throw std::runtime_error("Not enough operands.");
                }
                stack->push(node);
            }
            else if (str=="+" || str=="-" || str=="*" || str=="/" || str=="%") {
                operatorNode* node = new operatorNode(str);
                node->right = stack->pop();
                node->left = stack->pop();
                if (!node->left || !node->right) { 
                    delete node;
                    delete stack;
                    node = nullptr;
                    stack = nullptr;
                    throw std::runtime_error("Not enough operands.");
                }
                stack->push(node);
            }
            else {
                delete stack;
                throw std::runtime_error("Invalid token: " + str);
            }
        }
       
        

        
    }
    if (stack->indexSize()>1) {
        delete stack;
        throw std::runtime_error("Too many operands.");
    }
    if(stack->indexSize()==0) {
        delete stack;
        throw std::runtime_error("No input.");
    }
    AST* astnode =  stack->pop();
    delete stack;
    return astnode;
    
}
