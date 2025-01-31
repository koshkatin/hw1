/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include <cstddef>
#include <iostream>
#include "split.h"

class LL {
public: 
    LL() : head(NULL) {}
    LL(Node* h) : head(h) {}
    ~LL();
    void push_back(int v);
    Node* get_head() const;
    void set_head(Node* n);
private:
    Node* head;
};

void print(Node* h);
void deleteNode(Node* h);


int main(int argc, char* argv[])
{
    LL list;
    list.push_back(1);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);
    
    print(list.get_head());

    Node* listptr = list.get_head();
    Node* oddsptr = NULL;
    Node* evensptr = NULL;
    
    split(listptr, oddsptr, evensptr);
    // ^ changes listptr to 0, issues with deallocation
    // this is because the split function changes the original list
    // and does not create separate LLs for odds and evens.
    // in main we create an LL that split() disorganizes so it loses
    // track of nodes and causes delete issues. 
    
    print(oddsptr);
    print(evensptr);

    list.set_head(NULL);
    deleteNode(oddsptr);
    deleteNode(evensptr);

    print(list.get_head());

    return 0;
}

void LL::push_back(int v) 
{
    if (!head){
        head = new Node(v, NULL);   // create new node with value v
    }
    else {
        Node* temp = head;
        while(temp->next){
            temp = temp->next; 
        }
        temp->next = new Node(v, NULL);
    }
}

Node* LL::get_head() const
{
    return head;
}

void LL::set_head(Node* n)
{
    head = n;
}

LL::~LL()
{
    deleteNode(head);
}

void print(Node* head)
{
    Node* temp = head;
    while(temp){
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void deleteNode(Node* head)
{
    Node* temp = head;
    while(temp){
        Node* next = temp->next;
        delete temp;   
        temp = next;
    }
    head = NULL;
}
