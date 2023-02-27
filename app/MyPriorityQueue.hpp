#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>

class PriorityQueueEmptyException : public RuntimeException {
public:
  PriorityQueueEmptyException(const std::string &err) : RuntimeException(err) {}
};

template <typename Object> class MyPriorityQueue {
private:
  std::vector<Object> heap;

public:
  // You also need a constructor and a destructor.
  MyPriorityQueue();
  ~MyPriorityQueue();

  size_t size() const noexcept;
  bool isEmpty() const noexcept;

  void insert(const Object &elem);

  // Note:  no non-const version of this one.  This is on purpose because
  // the interior contents should not be able to be modified due to the
  // heap property.  This isn't true of all priority queues but
  // for this project, we will do this.
  // min and extractMin should throw PriorityQueueEmptyException if the queue is
  // empty.
  const Object &min() const;

  void extractMin();
};

template <typename Object>
MyPriorityQueue<Object>::MyPriorityQueue() : heap({}) {}

template <typename Object> MyPriorityQueue<Object>::~MyPriorityQueue() {}

template <typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept {
  return (size_t)heap.size();
}

template <typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept {
  return heap.empty();
}

template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem) {
  heap.push_back(elem);

  int cur = heap.size() - 1;
  int parent = (int)((cur - 1) / 2);

  while (parent > -1 && heap[cur] < heap[parent]) {
    std::swap(heap[cur], heap[parent]);
    cur = parent;
    parent = (int)((cur - 1) / 2);
  }
}

template <typename Object> const Object &MyPriorityQueue<Object>::min() const {
  if (isEmpty()) {
    throw PriorityQueueEmptyException("Priority queue is empty");
  }

  return heap[0];
}

template <typename Object> void MyPriorityQueue<Object>::extractMin() {
  if (isEmpty()) {
    throw PriorityQueueEmptyException("Priority queue is empty");
  } else if (heap.size() == 1) {
    heap.pop_back();
  } else {
    std::swap(heap[0], heap[heap.size() - 1]);
    int cur = 0;
    int child_1 = 2 * cur + 1, child_2 = 2 * cur + 2;

    heap.pop_back();

    while (child_1 < heap.size() || child_2 < heap.size()) {
      if (child_1 < heap.size() && child_2 < heap.size()) {
        int min_index = heap[child_1] < heap[child_2] ? child_1 : child_2;
        if (heap[cur] > heap[min_index]) {
          std::swap(heap[cur], heap[min_index]);
          cur = min_index;
          child_1 = 2 * cur + 1;
          child_2 = 2 * cur + 2;
        } else {
          break;
        }
      } else if (child_1 < heap.size()) {
        if (heap[cur] > heap[child_1]) {
          std::swap(heap[cur], heap[child_1]);
          cur = child_1;
          child_1 = 2 * cur + 1;
          child_2 = 2 * cur + 2;
        } else {
          break;
        }
      } else {
        if (heap[cur] > heap[child_2]) {
          std::swap(heap[cur], heap[child_2]);
          cur = child_2;
          child_1 = 2 * cur + 1;
          child_2 = 2 * cur + 2;
        } else {
          break;
        }
      }
    }
  }
}

#endif
