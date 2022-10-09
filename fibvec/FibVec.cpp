#include <stdexcept>

class FibVec {
    private:
        int *array;
        size_t length;
        size_t prevprevsize;
        size_t prevsize;
        size_t size;
        void shrink(){
            if (length < prevprevsize) {
                int *temp = array;
                array = new int[prevsize];
                for (int i = 0;i<length;i++) {
                    array[i] = temp[i];
                }
                delete[] temp;
                size = prevsize;
                prevsize = prevprevsize;
                prevprevsize = size - prevsize;
                if (prevprevsize < 1) {
                    prevprevsize = 1;
                }
            }
        } 
        void grow(){
            if (length == size) {
                prevprevsize = prevsize;
                prevsize = size;
                size = prevprevsize + prevsize;
                int *temp = array;
                array = new int[size];
                for (int i = 0;i<length;i++)  {
                    array[i] = temp[i];
                }
                delete[] temp;
            }
        }
    public:
        FibVec() {
            array = new int[1];
            length = 0;
            prevsize = 1;
            size = 1;
        }
        ~FibVec() {
            delete[] array;
        }

        const size_t capacity() {
            return length;
        }
        const size_t count() {
            return size;
        }
        void insert(int val, int ind) {
            grow();
            if (ind < 0 || ind > length-1) {
                throw std::out_of_range("index out of bounds in insert() function");
            }
            int temp = array[ind];
            array[ind] = val;
            int val = temp;
            for (int i = ind+1;i<length;i++) {
                temp = array[i];
                array[i] = val;
                val = temp;
            }
            array[length] = val;
            length++;
        }
        const int lookup(int ind) {
            return array[ind];
        }
        int pop() {
            if (length == 0) {
                throw std::underflow_error("underflow error in pop() function");
            }
            int val = array[length-1];
            array[length-1] = NULL;
            shrink();
            length--;
            return val;
        }
        void push(int val) {
            grow();
            array[length] = val;
            length++;
        }
        void remove(int ind) {
            if (ind < 0 || ind > length-1) {
                throw std::out_of_range("index out of bounds in remove() function");
            }
            for (int i = ind;i<length-1;i++) {
                array[ind] = array[ind+1];
            }
            array[length-1] = NULL;
            length--;
        }


};