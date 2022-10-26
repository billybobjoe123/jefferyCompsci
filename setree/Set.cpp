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
    Node::clean(mRoot);
    mRoot = nullptr;
}

size_t Set::clear() {
    size_t cnt =mRoot->size(mRoot);
    Node::clean(mRoot);
    mRoot = nullptr;
    return cnt;
    
}

bool Set::contains(const std::string& value) const {
    Node* ptr = this->mRoot;
    while(ptr) {
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
        return 1;
    }
    Node* ptr = this->mRoot;
    while(ptr) {
        if (ptr->data == Value) {
            return 0;
        }
        if (ptr->data > Value) {
            if (!ptr->left) {
                ptr->left = new Node(Value);

                return 1;
            }
            ptr = ptr->left;
        }
        else {
            if (!ptr->right) {
                ptr->right = new Node(Value);
                return 1;
            }
            ptr = ptr->right;
        }
    }
    return 0;
}
/**
Node* n1;
std::string lookupSize(Node* ptr, Node* mR,size_t n) {
    if (!ptr) {
        return "";
    }
    if (ptr->countless(mR,ptr->data) == n) {
        n1 = ptr;
        return ptr->data;
    }

    std::string temp1 = lookupSize(ptr->left,mR,n);
    std::string temp2 = lookupSize(ptr->right,mR,n);
    if (temp1 != "" && temp2!="") {
        return temp1;
    }
    return temp1 + temp2;
}
**/

int FlattenTreeIntoArray(Node* tree, std::string* array, int i){
    if (!tree) 
        return i;
    
    i = FlattenTreeIntoArray(tree->left, array, i);
    
    array[i] = tree->data;
    
    i = FlattenTreeIntoArray(tree->right, array, i + 1);
    return i;
} 


std::string str;
const std::string& Set::lookup(size_t n) const {
    size_t size = mRoot->size(mRoot);
    std::string arr[size];
    FlattenTreeIntoArray(mRoot,arr,0);
    if (n>=size) {
        throw std::out_of_range("out of range in lookup");
    }
    str = arr[n];
    return str;
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
        std::string str = "(" + printNodes(ptr->left) + " " + ptr->data + " " + printNodes(ptr->right) + ")";
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


Node* deleteNode(Node* node, std::string Value) {
    if(node) {
        if(Value < node->data) {
            node->left = deleteNode(node->left, Value);
        }    
       
        else if (Value > node->data) {
            node->right = deleteNode(node->right, Value);    
        }
        else if (Value == node->data) {
            if(!node->left && !node->right) {

                delete node;
                return nullptr;
            }          
        

            else if (node->left && !node->right) {
                Node* temp = node;
                node = node->left;
                delete temp;

                return node;
            }
            else if (!node->left && node->right) {
                Node* temp = node;
                node = node->right;
                delete temp;

                return node;
            }
            else if (node->left && node->right) {
                Node* temp = node->left; 
                int hasRight = 0;                    
                while(temp->right) {
                    hasRight = 1;
                    temp = temp->right;     
                }
                node->data = temp->data;
                if (hasRight)
                    deleteNode(node->left,temp->data);
                else {
                    node->left = nullptr;
                }
                return node;
            }
        }
    }
    return node;
}   

size_t Set::remove(const std::string& value) {
    
    
    if (!mRoot) {
        return 0;
    }
    size_t init = mRoot->size(mRoot);
    if (mRoot->data == value) {
        if(!mRoot->left && !mRoot->right) {
            delete mRoot;
            mRoot = nullptr;
            return 1;
        }
        if (!mRoot->left&& mRoot->right) {
            Node* temp = mRoot;
            mRoot = mRoot->right;
            delete temp;
            return 1;
        }
        if (!mRoot->right && mRoot->left) {
            Node* temp = mRoot;
            mRoot = mRoot->left;
            delete temp;
            return 1;
        }
        if (mRoot->left && mRoot->left) {
            Node* temp = mRoot->left; 
            int hasRight = 0;                    
            while(temp->right) {
                hasRight = 1;
                temp = temp->right;     
            }
            mRoot->data = temp->data;
            if (hasRight)
                deleteNode(mRoot->left,temp->data);
            else {
                mRoot->left = nullptr;
            }
            return 1;
            }
   

    this->mRoot = deleteNode(mRoot, value);
    init = init - mRoot->size(mRoot);
    return init;
    
}
}