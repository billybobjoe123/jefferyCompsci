#include "Nodes.h"
#include <sstream>
#include <stdexcept>
#include <cmath>
// Implement your AST subclasses' member functions here.
numberNode::numberNode(double val) {
    this->data = val;
}

std::string numberNode::prefix()  const{
    std::ostringstream stream;
    stream << data;
    return stream.str();
}

std::string numberNode::postfix() const {
    std::ostringstream stream;
    stream << data;
    return stream.str();
}

double numberNode::value()   const{
    return data;
}

operatorNode::operatorNode(std::string val) {
    this->data = val;
    this->left = nullptr;
    this->right = nullptr;
}

operatorNode::~operatorNode() {
    delete left;
    delete right;
}

std::string operatorNode::prefix()  const{
    if (this->data == "~") {
        return this->data + " " + this->left->prefix();
    }
    return this->data + " " + this->left->prefix() + " " + this->right->prefix();
}

std::string operatorNode::postfix() const {
    if (this->data == "~") {
        return this->left->postfix() + " " + this->data;
    }
    return this->left->postfix() + " " + this->right->postfix() + " " + this->data;
}

double operatorNode::value()   const{
    if (data == "+") {
        return left->value() + right->value();
    }
    else if(data == "-" ) {
        return left->value() - right->value();
    }
    else if(data == "*") {
        return left->value() * right->value();
    }
    else if(data == "/") {
        if (right->value()==0) {
            throw std::runtime_error("Division by zero.");
        }

        return left->value() / right->value();
    }
    else if(data == "%") {
        if (right->value()==0) {
            throw std::runtime_error("Division by zero.");
        }
        return remainder(left->value(),right->value());
    }
    else if(data == "~") {
        return left->value() * -1;
    }
    else {
        return 0;
    }
}






// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();
