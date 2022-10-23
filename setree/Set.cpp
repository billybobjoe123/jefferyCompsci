#include "Set.h"
#include "Node.h"
#include <stdexcept>
#include <iostream>

Set::Set() {
    this->mRoot = nullptr;
}
Node* copy(Node* other) {
    if(!other) {
        return nullptr;
    }
    Node* node = new Node(other->data);
    node->sub = other->sub;
    node->left = copy(other->left);
    node->right = copy(other->right);
    return node;
}

Set::Set(const Set& other) {
    this->mRoot = copy(other.mRoot);
}

Set::Set(Set&& other) {
    this->mRoot = other.mRoot;
    other.mRoot = nullptr;
}
Set::~Set() {
    mRoot->clean(mRoot);
}

size_t Set::clear() {
    return this->mRoot->clean(mRoot);
}

bool Set::contains(const std::string& value) const {
    Node* ptr = this->mRoot;
    while(!ptr) {
        if (ptr->data == value) {
            return true;
        }
        if (ptr->data > value) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }
    return false;
}
size_t Set::count() const {
    return this->mRoot->size(mRoot);
}
void Set::debug() {}

size_t Set::insert(const std::string& Value) {
    if (!this->mRoot) {
        mRoot = new Node(Value);
        mRoot->left = nullptr;
        mRoot->right = nullptr;
        return 1;
    }
    Node* ptr = this->mRoot;
    while(!ptr) {
        if (ptr->data == Value) {
            return 0;
        }
        if (ptr->data > Value) {
            if (!ptr->left) {
                ptr->left = new Node(Value);
                ptr->left->left = nullptr;
                ptr->left->right = nullptr;
                return 1;
            }
            ptr = ptr->left;
        }
        else {
            if (!ptr->right) {
                ptr->right = new Node(Value);
                ptr->right->left = nullptr;
                ptr->right->right = nullptr;
                return 1;
            }
            ptr = ptr->right;
        }
    }
    return 0;
}
Node* lookupLeftSize(Node* ptr, size_t n) {
    if (!ptr) {
        return nullptr;
    }
    if (ptr->leftsize(ptr) == n) {
        return ptr;
    }

    Node* temp1 = lookupLeftSize(ptr->left,n);
    Node* temp2 = lookupLeftSize(ptr->right,n);
    if (temp1) {
        return temp1;
    }
    if (temp2) {
        return temp2;
    }
    return nullptr;
    
}

const std::string& Set::lookup(size_t n) const {
    if (!this->mRoot) {
        throw std::out_of_range("out of range in lookup()");
    }
    Node* ptr = this->mRoot;
    ptr = lookupLeftSize(ptr,n);
    if (!ptr) {
        throw std::out_of_range("out of range in lookup()");
    }
    return ptr->data;
}
std::string printNodes(Node* ptr) {
    if (!ptr) {                   //null
        std::string str = "-";
        return str;
    }
    if (!ptr->left&&!ptr->right) { //leaf
        return ptr->data;
    }
    else {
        std::string str = "(" + printNodes(ptr->left) + ptr->data + printNodes(ptr->right) + ")";
        return str;
    }

}

void Set::print() const{
    if(this->mRoot) {
        std::cout<<printNodes(mRoot)<<std::endl;
    }
    else {
        std::cout<<"-"<<std::endl;
    }
}
size_t removal = 0;
Node* deleteNode(Node* node, std::string Value) {
    if(node) {
        if(Value < node->data) {
            node->left = deleteNode(node->left, Value);
        }    
       
        else if (Value > node->data) {
            node->right = deleteNode(node->right, Value);    
        }
        else {
            if(!node->left && !node->right) {
                removal++;
                return NULL;
            }          
            if (!node->left || !node->right) {
                removal++;
                if (node->left) {
                    return node->left;
                }
                return node->right;
            }
            removal++;                                                      
            Node* temp = node->left;                        
            while(!temp->right) {
                temp = temp->right;     
            }
            node->data = temp->data;                            
            node->left = deleteNode(node->left, temp->data);  
        }
    }
    return node;
}   

size_t Set::remove(const std::string& value) {
    this->mRoot = deleteNode(mRoot, value);
    return removal;
}

