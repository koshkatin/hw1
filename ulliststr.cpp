#include <cstddef>
#include <stdexcept>
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
    }
  }
  // ? other cases

  size_++;  // size increases in either case
}

void ULListStr::pop_back()
{
  // case I : empty list
  if (!tail_) return;
  
  // case II : non-empty list
  else {
    tail_->last--;  // move last index back
    tail_->val[tail_->last] = ""; // clear value at last element
    
    // check if array empties after popping
    if (tail_->last <= 0){
      Item* temp = tail_;
      tail_ = tail_->prev; 
      tail_->next = NULL;
      delete temp;
      temp->prev = NULL;
      temp->next = NULL;
      temp = NULL;
    }
  }


  size_--;  // decrease size in non-empty cases
}

void ULListStr::push_front(const std::string& val)
{
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
    }
  }

  size_++;
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  return nullptr;
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
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

ULListStr::Item* ULListStr::get_head() const 
{
  return head_;
}
