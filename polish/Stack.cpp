#include "Stack.h"
#include "Nodes.h"
Stack::Stack() {
    array = new AST*[200];
    index = 0;
    size = 200;
}
Stack::~Stack() {
    for (size_t i =0;i<index-1;i++) {
        delete array[i];
    }
    delete[] array;
}
void Stack::push(AST* node){
    if (node) {
        resize();
        array[index] = node;
        index++;
    }
}
AST* Stack::pop(){
    if (index == 0) {
        return nullptr;
    }
    index--;
    AST* node = array[index];
    array[index] = nullptr;
    return node;
}
void Stack::resize() {
    if (index==size-1) {
        AST* *temp = array;
        array = new AST*[size*2];
        for(size_t i = 0; i<size;i++) {
            array[i] = temp[i];
            temp[i] = nullptr;
        }
        delete[] temp; 
        size = size*2;
    }
}

size_t Stack::indexSize() {
    return index;
}
// Implement your Stack member functions here.
