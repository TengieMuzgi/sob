#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
using namespace std;

struct el {
    int v;
    el* next;
    el* prev;
    el();
    el(int v);
    virtual ~el();
};
//Struct constructor 
el::el() : v(0), next(nullptr), prev(nullptr) {}

//Struct constructor with parameter v
el::el(int v) : v(v), next(nullptr), prev(nullptr) {}

//Struct destructor

el::~el() {}
class List {
    el* head;	//First element address
    el* tail;	//Last element address
    float min;
    float max;

    //Adding element to list head
    el* addHead(int a) {
        assert(a >= min && a <= max);
        el* p = new el(a);
        //el* p = NULL;
        assert(p != NULL);
        if (head == nullptr) {
            head = tail = p;
        }
        else {
            head->prev = p;
            p->next = head;
            head = p;
        }
        return head;
    }

    //Adding element to list tail
    el* addTail(int a) {
        assert(a >= min && a <= max);
        el* p = new el(a);
        //el* p = NULL;
        assert(p != NULL);
        if (tail == nullptr) {
            head = tail = p;
        }
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
        return tail;
    }

    //Deleting element from list head
    el* removeHead() {
        el* p = head;
        if (head == nullptr) {
            return nullptr;
        }
        else if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete p;
        return head;
    }

    //Deleting element from list tail
    el* removeTail() {
        el* p = tail;
        if (tail == nullptr) {
            return nullptr;
        }
        else if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete p;
        return tail;
    }

public:

    List() : head(nullptr), tail(nullptr) {}

    List(float min, float max) : head(nullptr), tail(nullptr), min(min), max(max) {}

    //List destructor
    virtual ~List() {}

    //Add element to list in ascending order
    el* add(int a) {
        assert(a >= min && a <= max);
        el* p = head;
        while (p != nullptr && p->v < a) {
            p = p->next;
        }
        if (p == nullptr) {
            return addTail(a);
        }
        else if (p == head) {
            return addHead(a);
        }
        else {
            //el* temp = new el(a);
            el* temp = NULL;
            assert(temp != NULL);
            temp->prev = p->prev;
            temp->next = p;
            p->prev->next = temp;
            p->prev = temp;
            return temp;
        }
    }
    //Deleting element from list with given value 'a'
    el* removeValue(int a) {
        el* temp = head;
        while (temp) {
            if (temp->v == a) {
                if (temp == head) {
                    return removeHead();
                }
                else if (temp == tail) {
                    return removeTail();
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    return temp;
                }
            }
            temp = temp->next;
        }
        return nullptr;
    }

    //Deleting whole list
    void removeList() {
        el* temp = head;
        while (temp) {
            head = temp->next;
            delete temp;
            temp = head;
        }
        tail = nullptr;
    }

    //Show list content from right to left
    void showRightToLeft() {
        el* temp = tail;
        while (temp) {
            std::cout << temp->v << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }

    //Show list content from left to right
    void showLeftToRight() {
        el* temp = head;
        while (temp) {
            std::cout << temp->v << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void swap(el*& temp, el*& k) {
        if (temp == nullptr || k == nullptr) {
            return;
        }

        //Edge cases
        if (temp == head) {
            head = k;
        }
        else if (k == head) {
            head = temp;
        }
        if (temp == tail) {
            tail = k;
        }
        else if (k == tail) {
            tail = temp;
        }

        //Element swap
        el* temp_next = temp->next;
        temp->next = k->next;
        k->next = temp_next;

        el* temp_prev = temp->prev;
        temp->prev = k->prev;
        k->prev = temp_prev;

        if (temp_next != nullptr) {
            temp_next->prev = k;
        }
        if (temp->next != nullptr) {
            temp->next->prev = temp;
        }
        if (k->next != nullptr) {
            k->next->prev = k;
        }
        if (k->prev != nullptr) {
            k->prev->next = k;
        }
    }
};

int main(int argc, char* argv[])
{
    ifstream file("elements.txt");
    assert(file.is_open());

    float min_value = 0;
    float max_value = 0;

    sscanf(argv[1], "%f", &min_value);
    sscanf(argv[2], "%f", &max_value);

    List list = List(min_value, max_value);

    double value;
    while (file >> value) {
        list.add(value);
    }

    std::cout << "Showing list left to right\n";
    list.showLeftToRight();

    std::cout << "Showing list right to left\n";
    list.showRightToLeft();

    std::cout << "Removing value 4 \n";
    list.removeValue(4);

    std::cout << "Removing list\n";
    list.removeList();

    std::cout << "Closed file\n";
    file.close();

    return 0;

}

