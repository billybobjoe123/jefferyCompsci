#include "Heap.h"
#include <stdexcept>
Heap::Heap(size_t capacity) {
    mData = new Entry[capacity];
    mCapacity = capacity;
    mCount = 0;

}
Heap::Heap(const Heap& other) {
    
    mCapacity = other.capacity();
    mCount = other.count();
    mData = new Entry[mCapacity];
    for(size_t i = 0; i < mCount; i++) {
        Heap::Entry entry = other.lookup(i);
        this->push(entry.value,entry.score);
    }
}
Heap::Heap(Heap&& other) {
    this->mCapacity = other.capacity();
    this->mCount = other.count();
    mData = new Entry[mCapacity];
    for(size_t i = 0; i < count; i++) {
        Heap::Entry entry = other.pop();
        this->push(entry.value,entry.score);
    }

}
Heap::~Heap() {
    delete[] this->mData;
}
size_t Heap::capacity() const {
    return mCapacity;
}
size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index<mCount) {
        return mData[index];
    }   
    else {
        throw std::out_of_range("out of range in lookup function");
    }
}

Heap::Entry Heap::pop() {
    if(mCount<=0) {
        throw std::underflow_error("underflow in pop()");
    }
    Heap::Entry returnVal = mData[0];
    if (mCount==1)  {
        mCount--;
        return returnVal;
    }
    mData[0] = mData[mCount-1];
    mCount--;
    size_t ind = 0;
    while(ind<mCount) {
        if (ind*2+1<mCount && ind*2+2<mCount) {
            if (mData[ind].score>mData[ind*2+1].score && mData[ind*2+1].score<mData[ind*2+2].score) {
                Heap::Entry temp = mData[ind*2+1];
                mData[ind*2+1] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+1;
            }
            else if(mData[ind].score>mData[ind*2+2].score && mData[ind*2+1].score>mData[ind*2+2].score) {
                Heap::Entry temp = mData[ind*2+2];
                mData[ind*2+2] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+2;
            }
            else {
                break;
            }
        }
        else if(ind*2+1<mCount && ind*2+2>=mCount) {
            if(mData[ind*2+1].score<mData[ind].score) {
                Heap::Entry temp = mData[ind*2+1];
                mData[ind*2+1] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+1;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    
    return returnVal;   
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if(mCount<=0) {
        throw std::underflow_error("underflow in pushpop()");
    }
    Heap::Entry returnVal = mData[0];
    Heap::Entry insertEntry;
    insertEntry.score = score;
    insertEntry.value = value;
    
    mData[0] = insertEntry; 
    if (mCount==1){
        return returnVal;
    }
    size_t ind = 0;
    while(ind<mCount) {
        if (ind*2+1<mCount && ind*2+2<mCount) {
            if (mData[ind].score>mData[ind*2+1].score && mData[ind*2+1].score<mData[ind*2+2].score) {
                Heap::Entry temp = mData[ind*2+1];
                mData[ind*2+1] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+1;
            }
            else if(mData[ind].score>mData[ind*2+2].score && mData[ind*2+1].score>mData[ind*2+2].score) {
                Heap::Entry temp = mData[ind*2+2];
                mData[ind*2+2] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+2;
            }
            else {
                break;
            }
        }
        else if(ind*2+1<mCount && ind*2+2>=mCount) {
            if(mData[ind*2+1].score<mData[ind].score) {
                Heap::Entry temp = mData[ind*2+1];
                mData[ind*2+1] = mData[ind];
                mData[ind] = temp;
                ind = ind*2+1;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    return returnVal;
}

void Heap::push(const std::string& value, float score) {
    if (mCapacity==mCount) {
        throw std::overflow_error("Overflow in push()");
    }
    //insert
    Heap::Entry insertEntry;
    insertEntry.score = score;
    insertEntry.value = value;
    mData[mCount] = insertEntry;
    //percolate up
    size_t ind = mCount;
    while(ind!=0) {
        if(mData[ind].score<mData[(ind-1)/2].score) {
            Heap::Entry temp = mData[(ind-1)/2];
            mData[(ind-1)/2] = mData[ind];
            mData[ind] = temp;
            ind = (ind-1)/2;
        }
        else {
            break;
        }
    }
    mCount++;
}

const Heap::Entry& Heap::top() const {
    if(mCount==0) {
        throw std::underflow_error("underflow in top()");
    }  
    return mData[0];
}