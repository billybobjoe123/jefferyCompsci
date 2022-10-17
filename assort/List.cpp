#include "List.h"
#include <stdexcept>
#include <iostream>
List::List() {
    head = NULL;
} 
List::List(const List& other) {//copy
    
    if (other.head == NULL) {
        head = NULL;
        return;
    }
    head = new Node;
    Node* curr = head;
    Node* otherCurr = other.head;
    head->next = NULL;
    while (true) {
        if (otherCurr == NULL) {
            break;
        }
        if (curr->next == NULL && otherCurr->next != NULL) {
            curr->next = new Node;
            curr->next->next = NULL;
        }
        
        curr->data = otherCurr->data;
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
}
List::List(List&& other) {//move
    head = other.head;
    other.head = NULL;
}
List::~List() {
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
}
size_t List::count() const {
    
    if (head == NULL) {
        return 0;
    }
    Node* curr = head;
    size_t cnt = 0;
    while (true) {
        if (curr->next == NULL) {
            cnt++;
            break;
        }
        curr = curr->next;
        cnt++;
    }                  
    return cnt;
}
void List::insert(const std::string& value) {
    if (head == NULL) {
        head = new Node;
        head->data = value;
        head->next = NULL;
        return;
    }
    if (value < head->data) {
        Node* temp = head;
        head = new Node;
        head->next = temp;
        head->data = value;
        temp = NULL;
        return;
    }
    Node* curr = head;
    Node* next = head->next;
    while (true) {
        if (next == NULL) {
            curr->next = new Node;
            curr->next->data = value;
            curr->next->next = NULL;
            return;
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
    if (index == 0) {
        return head->data;
    }
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
        delete[] arr;
        std::cout<<"[]"<< std::endl;
        return;
    }
    
    if (!reverse) {
        curr = head;
        std::cout<<"["<<curr->data;
        curr = curr->next;
        while (curr != NULL) {
            std::cout<<", "<<curr->data;
            curr = curr->next;
        }
        std::cout<<"]"<<std::endl;
    }
    else {
        int cnt = 0;
        curr = head;
        
        while (curr->next != NULL) {
            
            if (cnt+1 == int(sizeof(arr))) {
                std::string *temp = arr;
                arr = new std::string[sizeof(arr)*2];
                for(int i = 0; i<int(sizeof(temp));i++) {
                    arr[i] = temp[i];
                }
                delete[] temp;
            }
            arr[cnt] = curr->data;
            curr = curr->next;
            cnt++;
        }
        
        std::cout<<"["<<curr->data;
        for (int i = cnt-1; i>=0;i--) {
            std::cout<<", "<<arr[i];
        }
        std::cout<<"]"<<std::endl;
    }
    delete[] arr;
    
}


std::string List::remove(size_t index) {
    Node* curr = head;
    if (curr == NULL) {
        throw std::out_of_range("out of range in remove");
    }
    Node* next = curr->next;

    size_t count = 0;
    if (index == 0) {
        Node* temp = head;
        std::string str = head->data;
        head = head->next;
        delete temp;
        temp = NULL;
        return str;
    }
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
        
        if (curr->data == value) {
            Node* temp = curr;
            curr = next;
            next = next->next;
            delete temp;
            count++;
        }
        if (next==NULL) {
            break;
        }
        curr = next;
        next = next->next;

    }     
    return count;                        
}
