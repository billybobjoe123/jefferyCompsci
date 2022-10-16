#include "List.h"
#include <stdexcept>
#include <iostream>
List::List() {
    head = NULL;
} 
List::List(const List& other) {//copy

    Node* current = new Node;
    current->data = other.head->data;
    Node* otherCurr = other.head;
    while(true) {
        if (current == NULL) {
            current = new Node;
            current->next = NULL;
        }
        if (otherCurr->next == NULL && current->next!= NULL) {
            Node* tempcur = current->next;
            Node* tempNext = tempcur->next;
            current->next = NULL;
            while (true) {
                delete tempcur;
                tempcur = NULL;
                if (tempNext == NULL) {
                    break;
                }
                tempcur = tempNext;
                tempNext = tempNext->next;
            }
        }
        if (otherCurr == NULL) {
            break;
        }
        current->data = otherCurr->data;
        current = current->next;
        otherCurr = otherCurr->next;
        

    }
}
List::List(List&& other) {//move
    head = other.head;
    other.head = NULL;
}
List::~List() {
    
}
size_t List::count() const {
    Node* curr = head;
    int cnt = 0;
    while (true) {
        if (curr->next == NULL) {
            cnt++;
            break;
        }
        curr = curr->next;
    }
}
void List::insert(const std::string& value) {
    if (head == NULL) {
        head = new Node;
        head->data = value;
        return;
    }
    if (value < head->data) {
        Node* temp = head;
        head = new Node;
        head->next = temp;
        head->data = value;
        return;
    }
    Node* curr = head;
    Node* next = head->next;
    while (true) {
        if (next == NULL) {
            curr->next = new Node;
            curr->next->data = value;
            curr->next->next = NULL;
        }
        else {
            if (curr->data < value && next->data > value) {
                Node* temp = next;
                curr->next = new Node;
                curr->next->next = temp;
                curr->next->data = value;
                return;
            }
            else {
                curr = next;
                next = curr->next;
            }
        }



    }
}
const std::string& List::lookup(size_t index) const {
    Node* curr = head;
    if (curr == NULL) {
        throw std::out_of_range("out of range in lookup");
    }
    Node* next = curr->next;

    size_t count = 0;
    while (true) {
        if (count == index-1) {
            if (next==NULL) {
                throw std::out_of_range("out of range in lookup");
            }
            else{
                return next->data;
            }
        }
        if (next == NULL) {
            throw std::out_of_range("out of range in lookup");
        }
        curr = next;
        next = next->next;
        count++;
    }
}
void List::print(bool reverse) const {
    std::string *arr = new std::string[1000];
    Node* curr = head;
    if (head==NULL) {
        return;
    }
    int cnt = 0;
    while (curr->next != NULL) {
        if (cnt+1 == int(sizeof(arr))) {
            std::string *temp = arr;
            arr = new std::string[sizeof(arr)*2];
            for(int i = 0; i<int(sizeof(temp));i++) {
                arr[i] = temp[i];
            }
        }
        arr[cnt] = curr->data;
        curr = curr->next;
        cnt++;
    }
    if (reverse) {
        std::cout<<"["<<arr[cnt];
        for (int i = cnt-1; i>=0;i--) {
            std::cout<<", "<<arr[i];
        }
        std::cout<<"]"<<std::endl;
    }
    else {
        std::cout<<"["<<arr[0];
        for (int i = 1; i<=cnt;i--) {
            std::cout<<", "<<arr[i];
        }
        std::cout<<"]"<<std::endl;
    }
    
}


std::string List::remove(size_t index) {
    Node* curr = head;
    if (curr == NULL) {
        throw std::out_of_range("out of range in remove");
    }
    Node* next = curr->next;

    size_t count = 0;
    while (true) {
        if (count == index-1) {
            if (next==NULL) {
                throw std::out_of_range("out of range in remove");
            }
            else{
                std::string value = next->data;
                curr->next = next->next;
                delete next;
                next = NULL;
                return value;
            }
        }
        if (next == NULL) {
            throw std::out_of_range("out of range in remove");
        }
        curr = next;
        next = next->next;
        count++;
    }
}
size_t List::remove(const std::string& value) {
    Node* curr = head;
    if (curr == NULL) {
        return 0;
    }
    Node* next = curr->next;

    size_t count = 0;
    while (true) {
        if (next==NULL) {
            break;
        }
        else{
            std::string value = next->data;
            curr->next = next->next;
            delete next;
            next = NULL;
            count++;
        }
        curr = next;
        next = next->next;

    }     
    return count;                        
}
