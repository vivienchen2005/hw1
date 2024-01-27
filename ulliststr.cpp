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
  //case: no items
  if (head_ == nullptr && tail_ == nullptr) {
    Item* temp = new Item();
    temp->last = 1;
    temp->val[0] = val;
    head_ = temp;
    tail_ = temp;
  }
  else {
    if (tail_->last == ARRSIZE) {
      Item* temp = new Item();
      temp->val[0] = val;
      temp->last = 1;
      temp->prev = tail_;
      tail_->next = temp;
      tail_ = temp;
    }
    else {
      tail_->val[(tail_->last)] = val;
      tail_->last += 1;
    }
  }
  size_ += 1;
}

void ULListStr::push_front(const std::string& val) 
{
  if (head_ == nullptr && tail_ == nullptr) {
    Item* temp = new Item();
    temp->first = ARRSIZE - 1;
    temp->last = ARRSIZE;
    temp->val[ARRSIZE-1] = val;
    head_ = temp;
    tail_ = temp;
  }
  else {
    if (head_->first == 0) {
      Item* temp = new Item();
      temp->val[ARRSIZE-1] = val;
      temp->first = ARRSIZE-1;
      temp->last = ARRSIZE;
      temp->next = head_;
      head_->prev = temp;
      head_ = temp;
    }
    else {
      head_->val[(head_->first) - 1] = val;
      head_->first -= 1;
    }
  }
  size_ += 1;
}

void ULListStr::pop_back()
{
  if (head_ == nullptr && tail_ == nullptr) {
    return;
  }
  else {
    //case: tail has only 1 element
    if (((tail_->last) - (tail_->first)) == 1) {
      //subcase: more than 1 item
      Item* temp = tail_;
      if (head_ != tail_) {
         tail_ = tail_->prev;
         tail_->next = nullptr;
      }
      //subcase: 1 item
      else {
        tail_ = nullptr;
        head_ = nullptr;
      }
      delete temp;
    }
    //case: tail has more than 1 item
    else {
      tail_->last -= 1;
    }
    size_ -= 1;
  }
}

void ULListStr::pop_front()
{
  if (head_ == nullptr && tail_ == nullptr) {
    return;
  }
  //case: 1 or more items
  else {
    //case: head has only 1 element
    if (((head_->last) - (head_->first)) == 1) {
      Item* temp = head_;
      //subcase: more than 1 item
      if (head_ != tail_) {
         head_ = head_->next;
         head_->prev = nullptr;
      }
      //subcase: 1 item
      else {
        tail_ = nullptr;
        head_ = nullptr;
      }
      delete temp;
    }
    //case: head has more than 1 item
    else {
      head_->first += 1;
    }
    size_ -= 1;
  }
}

std::string const & ULListStr::back() const 
{
  if (head_ == nullptr && tail_ == nullptr) {
    return NULL;
  }
  else {
    return tail_->val[tail_->last - 1];
  }
}

std::string const & ULListStr::front() const 
{
  if (head_ == nullptr && tail_ == nullptr) {
    return NULL;
  }
  else {
    return head_->val[head_->first];
  }
}

/** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc < size_ && loc >= 0) {
    Item* current = head_;
    size_t count = 0;
    while (current != nullptr && count + (current->last) - (current->first) <= loc) {
      count += (current->last) - (current->first);
      current = current->next;
    }
    if (current != nullptr) {
      return &(current->val[loc - count + current->first]);
    }
  }
  else {
    return NULL;
  }
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
