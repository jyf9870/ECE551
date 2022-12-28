#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class itemNotExistException : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & data) : data(data), next(NULL), prev(NULL){};
    Node(const T & data, Node * next, Node * prev) : data(data), next(next), prev(prev){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      this->addBack(curr->data);
      curr = curr->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList tmp(rhs);
      Node * original_head = head;
      head = tmp.head;
      tmp.head = original_head;
      Node * original_tail = tail;
      tail = tmp.tail;
      tmp.tail = original_tail;
      size = tmp.size;
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    // if (this->size == 0) {
    //   Node * first = new Node(item);
    //   this->head = first;
    //   this->tail = first;
    //   size++;
    // }
    // else {
    //   Node * temp = new Node(item);

    //   temp->next = this->head;
    //   this->head->prev = temp;
    //   this->head = temp;
    //   size++;
    // }

    Node * first = new Node(item);
    first->next = head;
    head = first;
    if (size == 0) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    // if (this->size == 0) {
    //   Node * end = new Node(item);
    //   this->head = end;
    //   this->tail = end;
    //   size++;
    // }
    // else {
    //   Node * temp = new Node(item);
    //   temp->prev = this->tail;
    //   this->tail->next = temp;
    //   this->tail = temp;
    //   size++;
    // }

    Node * end = new Node(item);
    end->prev = tail;
    tail = end;
    if (size == 0) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    if (this->size == 0)
      return false;

    Node ** curr = &head;
    int i = 0;
    while (*curr != NULL && (*curr)->data != item) {
      curr = &((*curr)->next);

      assert(i < this->size);
      i++;
    }
    if (*curr == NULL)
      return false;

    Node * rmNode = *curr;
    *curr = rmNode->next;
    if (rmNode->next != NULL) {
      rmNode->next->prev = rmNode->prev;
      //      rmNode->prev->next = rmNode->next;
    }
    if (this->tail == rmNode) {
      this->tail = rmNode->prev;
    }
    delete rmNode;
    this->size--;
    return true;
  }

  T & operator[](int index) {
    if (index < 0 && index >= size) {
      throw new itemNotExistException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      assert(curr != NULL);
      curr = curr->next;
    }
    return curr->data;
  }

  const T & operator[](int index) const {
    if (index < 0 && index >= size) {
      throw new itemNotExistException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      assert(curr != NULL);
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) const {
    Node * curr = head;
    for (int i = 0; curr != NULL; i++) {
      if (curr->data == item) {
        return i;
      }
      curr = curr->next;
    }
    return -1;
  }
  friend class Tester;
};
#endif
