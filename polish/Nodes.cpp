#include "Nodes.h"

#include <cmath>
// Implement your AST subclasses' member functions here.
numberNode::numberNode(int val) {
    this->data = val;
}

std::string numberNode::prefix()  const{
    return std::to_string(this->data);
}

std::string numberNode::postfix() const {
    return std::to_string(this->data);
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
    return this->left->postfix() + " " + this->right->postfix() + this->data;
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
        return left->value() / right->value();
    }
    else if(data == "%") {
        return remainder(left->value(),right->value());
    }
    else if(data == "~") {
        return left->value() * -1;
    }
}






// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();
