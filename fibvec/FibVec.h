#include <cstddef>
#pragma once
#ifndef FibVec_H
#define FibVec_H
// code
class FibVec {
    private:
        int *array;
        size_t length;
        size_t prevprevsize;
        size_t prevsize;
        size_t size;
        void shrink();
        void grow();
    public:
        FibVec();
        ~FibVec();

        size_t capacity() const; 
        size_t count() const; 
        void insert(int val, size_t ind);
        int lookup(size_t ind) const ;
        int pop();
        void push(int val);
        void remove(size_t ind);


};

#endif