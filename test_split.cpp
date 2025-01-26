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
    Node* head;
    
public: 
    LL() : head(NULL) {}
    LL(Node* n) : head(n) {}
    ~LL();
    void push_back(int v);
    void print();
    Node* get_head() const;

};

int main(int argc, char* argv[])
{
    LL list;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);
    
    list.print();

    Node* listptr = list.get_head();
    Node* oddsptr = NULL;
    Node* evensptr = NULL;
    split(listptr, oddsptr, evensptr);

    LL odds(oddsptr);
    LL evens(evensptr);

    odds.print();
    evens.print();

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

void LL::print()
{
    Node* temp = head;
    while(temp){
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

Node* LL::get_head() const
{
    return head;
}

LL::~LL()
{
    while(head){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}