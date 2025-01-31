#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  // // --- v.ii : clean/concise ---

  //   if (tail_ == NULL){
  //   tail_ = new Item; 
  //   head_ = tail_;
  //   }
  //   else if (tail_->last == ARRSIZE){
  //     Item* newItem = new Item;
  //     newItem->prev = tail_;
  //     tail_->next = newItem;
  //     tail_ = newItem;
  //   }

  //   tail_->val[tail_->last] = val;
  //   tail_->last++;
  //   size_++;

  // // --------- * ----------
  

  // --- v.i : redundant/detailed ---

    Item* newItem = new Item;

    // case I : empty list
    if (tail_ == NULL){   
      newItem->first = 0;   // place at first index
      newItem->val[newItem->first] = val; // [v][ ][ ][ ]
      newItem->last = newItem->first + 1; // [f][l][ ][ ] ++ bounds checking? 
      // prev and next are still null

      head_ = tail_ = newItem;  // point head and tail to new item
    }
    else {
      // case II : non-empty list, right-full array
      if (tail_->last >= ARRSIZE){ // indicates end-full array
        newItem->first = 0;   // place at first index for congruity
        newItem->val[newItem->first] = val; // [v][ ][ ][ ]
        newItem->last = newItem->first + 1; // [f][l][ ][ ] ++ bounds checking? 
        newItem->prev = tail_;  // connect newitem to previous node
        newItem->next = NULL;   // last node

        tail_->next = newItem;  // connect previous node to newitem
        tail_ = newItem;  // update tail to newitem 
      }
      // case III : non-empty list, right-free array 
      else {  
        tail_->val[tail_->last] = val;         // [*][*][l][ ]
        tail_->last++;  // increment last index   [*][*][v][l]
        delete newItem;
      }
    }

    size_++;  // size increases in either case

  // --------------- * --------------
}

void ULListStr::pop_back()
{
  // case I : empty list
  if (!tail_) return;
  
  // case II : non-empty list, non-empty array
  tail_->last--;  // move last index back
  tail_->val[tail_->last] = ""; // clear value at last element
  
  // case III : non-empty list, empty array >> delete node
  if (tail_->last == 0) { // check if array empties after popping
    Item* temp = tail_;
    tail_ = tail_->prev; 
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr; // List is now empty
    }
    delete temp;
  }
  
  size_--;  // decrease size in non-empty cases
}

void ULListStr::push_front(const std::string& val)
{
  // // --- v.ii : clean/concise ---

  //   if (head_ == NULL) { // List is empty
  //     head_ = new Item();
  //     tail_ = head_;
  //   } 
  //   else if (head_->first == 0) { // First item is full at the front
  //     Item* newItem = new Item();
  //     newItem->next = head_;
  //     head_->prev = newItem;
  //     head_ = newItem;
  //   }

  //   head_->first--;
  //   head_->val[head_->first] = val;
  //   size_++;

  // // --------- * ----------

  
  // --- v.i : redundant/detailed ---

    Item* newItem = new Item;

    // case I : empty list
    if (head_ == NULL){
      newItem->first = ARRSIZE - 1;        // [ ][ ][ ][f]
      newItem->val[newItem->first] = val;  // [ ][ ][ ][v]
      newItem->last = newItem->first + 1;  // [ ][ ][ ][f] l
      // prev = next = null

      head_ = tail_ = newItem;
    }
    else {
      // case II : non-empty list, left-full array
      if (head_->first <= 0){
        newItem->first = ARRSIZE - 1;        // [ ][ ][ ][f]
        newItem->val[newItem->first] = val;  // [ ][ ][ ][v]
        newItem->last = newItem->first + 1;  // [ ][ ][ ][f] l
        newItem->prev = NULL;
        newItem->next = head_;

        head_->prev = newItem;
        head_ = newItem;
      }
      // case III : non-empty list, left-free array
      else {
        head_->first--; // move first ptr back 
        head_->val[head_->first] = val; // [v][f][*][ ]
        delete newItem;
      }
    }

    size_++;

  // --------------- * --------------
}

void ULListStr::pop_front()
{
  // case I : empty list
  if (!head_) return; 

  // case II : non-empty list, non-empty array
  head_->val[head_->first] = "";  // [ ][ ][x][*]
  head_->first++;                 // [ ][ ][ ][f]
  
  // case III : non-empty list, empty array
  if (head_->last == head_->first) {
    Item* temp = head_;
    head_ = head_->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr; // List is now empty
    }
    delete temp;
  }
  
  size_--;
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last - 1];
}


std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  // return NULL if loc is invalid
  if (loc < 0 || loc >= size_) return NULL;
  Item* curr = head_;

  // determine which node the location falls in
  // add the first index to loc to shift it forward appropriately 
  size_t rank = (loc + head_->first) / ARRSIZE;  
  
  Item* node = listRecurser(curr, rank);
  
  size_t idx;
  idx = (loc + head_->first) % ARRSIZE; 

  return &(node->val[idx]);
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while (head_ != nullptr) {
    Item* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = nullptr;
  size_ = 0;
}

ULListStr::Item* ULListStr::get_head() const 
{
  return head_;
}

ULListStr::Item* ULListStr::listRecurser(Item* node, size_t rank) const
{
  if (node == NULL) return NULL;  // not found
  if (rank == 0) return node;     // found!
  rank--;   // decrementing rank means moving to next node
  return listRecurser(node->next, rank);
}

