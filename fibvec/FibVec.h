#include <cstddef>

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

        const size_t capacity();
        const size_t count();
        void insert(int val, int ind);
        const int lookup(int ind);
        int pop();
        void push(int val);
        void remove(int ind);


};

#endif