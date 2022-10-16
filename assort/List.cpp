#include "List.h"
List::List() {
    head = NULL;
} 
List::List(const List& other) {//copy

    Node* current = head;
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
    return 0;
}
void List::insert(const std::string& value) {

}
const std::string& List::lookup(size_t index) const {
    std::string str = "";
    return str;
}
void List::print(bool reverse = false) const {

}

std::string List::remove(size_t index) {
    std::string str = "";
    return str;
}
size_t List::remove(const std::string& value) {
    return 0;                                   
}
