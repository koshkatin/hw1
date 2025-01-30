/*
CSCI 104: Homework 1 Problem 1 

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  if (!in) return;  // base case: NULL input
  
  Node* next = in->next;  // save the next input node

  if (in->value % 2 == 0) { 
    evens = new Node(in->value, evens);
  } else {
    odds = new Node(in->value, odds);
  }

  split(next, odds, evens);  // recurse

  in = NULL; // set the original list to NULL to prevent dangling ptrs
}

/* If you needed a helper function, write it here */
