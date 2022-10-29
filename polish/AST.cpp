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
        if (std::stod(str)) {
            double number = std::stod(str);
            numberNode *n = new numberNode(number);
            stack->push(n);
        }
        else {
            std::string s = str;
            if (s=="~") {
                operatorNode* node = new operatorNode(str);
                node->left = stack->pop();
                if (!node->left) { 
                    delete node;
                    delete stack;
                    node = nullptr;
                    stack = nullptr;
                    throw std::runtime_error("not enough operands.");
                }
                stack->push(node);
            }
            else if (s=="+" || s=="-" || s=="*" || s=="/" || s=="%") {
                operatorNode* node = new operatorNode(str);
                node->left = stack->pop();
                node->right = stack->pop();
                if (!node->left || !node->right) { 
                    delete node;
                    delete stack;
                    node = nullptr;
                    stack = nullptr;
                    throw std::runtime_error("Mot enough operands.");
                }
                if (s=="/" || s=="%") {
                    if (node->right->value() == 0) {
                        delete node;
                        delete stack;
                        node = nullptr;
                        stack = nullptr;
                        throw std::runtime_error("Division by zero.");
                    }
                }
                stack->push(node);
            }
            else {
                std::string error = "Invalid token: " + str;
                delete stack;
                throw std::runtime_error(error);
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
    return stack->pop();
}
