#include <stdexcept>
#include "FibVec.h"

void FibVec::shrink(){
    if (length < prevprevsize) {
        int *temp = array;
        array = new int[prevsize];
        for (size_t i = 0;i<length;i++) {
            array[i] = temp[i];
        }
        delete[] temp;
        size = prevsize;
        prevsize = prevprevsize;
        prevprevsize = size - prevsize;
        if (prevprevsize ==0) {
            prevprevsize = 1;
        }
    }
} 
void FibVec::grow(){
    if (length == size) {
        prevprevsize = prevsize;
        prevsize = size;
        size = prevprevsize + prevsize;
        int *temp = array;
        array = new int[size];
        for (size_t i = 0;i<length;i++)  {
            array[i] = temp[i];
        }
        delete[] temp;
    }
}

FibVec::FibVec() {
    array = new int[1];
    length = 0;
    prevprevsize = 1;
    prevsize = 1;
    size = 1;
}
FibVec::~FibVec() {
    delete[] array;
}

size_t FibVec::capacity() const 
{
    return size;
}
size_t FibVec::count() const 
{
    return length;
}
void FibVec::insert(int val, size_t ind) {
    
    
    if (ind > length) {
        throw std::out_of_range("index out of bounds in insert() function");
    }
    if (length+1>size) {
        grow();
    }
    if (ind == length) {
        array[length] = val;
        length++;
        return;
    }
    if (length !=0) {
        int temp;
        for (size_t i = ind;i<length;i++) {
            temp = array[i];
            array[i] = val;
            val = temp;
        }
        array[length] = val;
        length++;
    }
    else {
        array[0] = val;
        length++;
    }
}
int FibVec::lookup(size_t ind) const 
{
    if (ind>=length) {
        throw std::out_of_range("index out of bounds in lookup() function");
    }
    return array[ind];
}
int FibVec::pop() {
    
    if (length == 0) {
        throw std::underflow_error("underflow error in pop() function");
    }
    int val = array[length-1];
    //array[length-1] = NULL;
    length--;
    shrink();
    return val;
}
void FibVec::push(int val) {
    if (length+1>size) {
        grow();
    }
    array[length] = val;
    length++;
    
}
int FibVec::remove(size_t ind) {

    if (ind > length) {
        throw std::out_of_range("index out of bounds in remove() function");
    }
    int val = array[ind];
    if (length>1) {
        for (size_t i = ind;i<length-1;i++) {
            array[i] = array[i+1];
        }
        //array[length-1] = NULL;
        
    }
    if (ind == length-1) {
        length--;
        shrink();
    }
    return val;
    
}


